\name{asne-package}
\alias{asne-package}
\alias{asne}
\docType{package}
\title{
\packageTitle{asne}
}
\description{
\packageDescription{asne}
}
\details{

The DESCRIPTION file:
\packageDESCRIPTION{asne}
\packageIndices{asne}

A rough wrapping of A-tSNE from High Dimensionality Inspector package. Build system is a wreck and requires a bit of human intervention.
}
\author{
\packageAuthor{asne}

Maintainer: \packageMaintainer{asne}
}
\references{
Pezzotti, N., Lelieveldt, B. P., van der Maaten, L., Höllt, T., Eisemann, E., & Vilanova, A. (2017). Approximated and user steerable tSNE for progressive visual analytics. IEEE transactions on visualization and computer graphics, 23(7), 1739-1752.
}
\keyword{ package }
\keyword{ tsne }
\keyword{ embedding }
\examples{
m <- dataEachDatapointOnSeparateRow
res <- ASNE(m, target_dims=2, iters=1000, exiters=250, perplexity=30, theta=0.5)
plot(res$embedding[,1], res$embedding[,2])
}
