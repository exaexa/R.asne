
ASNE <- function(datapoints,target_dims=2,iters=1000,exiters=250,perplexity=30,theta=0.5) {
	embedding=matrix(0, nrow=nrow(datapoints), ncol=target_dims)

	res <- .C("C_ASNE",
		input=as.double(datapoints),
		output=as.double(embedding),
		n=as.integer(nrow(datapoints)),
		in_dim=as.integer(ncol(datapoints)),
		out_dim=as.integer(target_dims),
		iters=as.integer(iters),
		exaggerated=as.integer(exiters),
		pPerplexity=as.integer(perplexity),
		pTheta=as.double(theta))
	
	mtx <- matrix(res$output, nrow(embedding), ncol(embedding))
	
	list(embedding=mtx)
}
