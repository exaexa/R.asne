
#include <R.h>
#include <Rmath.h>
#include <R_ext/PrtUtil.h>
#include <R_ext/Rdynload.h>

#include <iostream>
using namespace std;

#include "hdi/dimensionality_reduction/tsne.h"
#include "hdi/data/embedding.h"
#include "hdi/dimensionality_reduction/hd_joint_probability_generator.h"
#include "hdi/dimensionality_reduction/sparse_tsne_user_def_probabilities.h"

typedef float scalar_type;

extern "C"
void C_ASNE (double*input,
             double*output,
             int* n,
             int*in_dim,
             int*out_dim,
             int*iters,
             int*exaggerated,
             int*pPerplexity,
             double*pTheta)
{
	int num_data_points = *n,
	    num_dimensions = *in_dim,
	    num_target_dimensions = *out_dim,
	    perplexity = *pPerplexity,
	    iterations = *iters,
	    exaggeration_iter = *exaggerated;
	double theta = *pTheta;

	/* good defaults:
	bool verbose                = false;
	int iterations              = 1000;
	int exaggeration_iter       = 250;
	int perplexity              = 30;
	double theta                = 0.5;
	int num_target_dimensions   = 2;
	 */

	hdi::dr::HDJointProbabilityGenerator<scalar_type> prob_gen;
	hdi::dr::HDJointProbabilityGenerator<scalar_type>::sparse_scalar_matrix_type distributions;
	hdi::dr::HDJointProbabilityGenerator<scalar_type>::Parameters prob_gen_param;
	hdi::dr::SparseTSNEUserDefProbabilities<scalar_type> tSNE;
	hdi::dr::SparseTSNEUserDefProbabilities<scalar_type>::Parameters tSNE_param;
	hdi::data::Embedding<scalar_type> embedding;


	std::vector<scalar_type> scalar_data;
	scalar_data.resize (num_data_points * num_dimensions);
	for (size_t i = 0; i < num_data_points; ++i) for (size_t j = 0; j < num_dimensions; ++j)
			scalar_data[num_dimensions * i + j] = input[i + num_data_points*j];

	cerr << "computing probability distributions..." << endl;
	prob_gen_param._perplexity = perplexity;
	prob_gen.computeProbabilityDistributions (scalar_data.data(),
	                                          num_dimensions,
	                                          num_data_points,
	                                          distributions,
	                                          prob_gen_param);


	tSNE_param._embedding_dimensionality = num_target_dimensions;
	tSNE_param._mom_switching_iter = exaggeration_iter;
	tSNE_param._remove_exaggeration_iter = exaggeration_iter;
	cerr << "initializing SNE..." << endl;
	tSNE.initialize (distributions, &embedding, tSNE_param);
	tSNE.setTheta (theta);

	cerr << "starting iterations..." << endl;
	for (int iter = 0; iter < iterations; ++iter) {
		if (! ( (iter + 1) % (iterations >> 3))) cerr << iter << "..." << endl;
		tSNE.doAnIteration();
	}

	cerr << "almost done..." << endl;
	scalar_type* result_scalar_data = embedding.getContainer().data();
	for (size_t i = 0; i < num_data_points; ++i) for (size_t j = 0; j < num_target_dimensions; ++j)
			output[i + num_data_points*j] = result_scalar_data[num_target_dimensions * i + j];
}

static const R_CMethodDef cMethods[] = {
	{"C_ASNE", (DL_FUNC) &C_ASNE, 9},
	{NULL, NULL, 0}
};

extern "C"
void R_init_asne (DllInfo*info)
{
	R_registerRoutines (info, cMethods, NULL, NULL, NULL);
}
