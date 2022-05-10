# Materials for "Global Effects of Marine Protected Areas on Food Security Are Unknown"

This repository contains all the materials needed to reproduce the "Matters Arising" titled "Global Effects of Marine Protected Areas on Food Security Are Unknown", in response to Sala *et al.* (2021). Pre-print available [here](https://figshare.com/articles/preprint/Global_Effects_of_Marine_Protected_Areas_on_Food_Security_Are_Unknown/16709362)



## Setup

In order to reproduce

1. Fork the repository and clone to your machine (or download a local version)

2. Open R and set your working directory of the cloned repository (or just use RStudio projects)

3. This project is set up with [`renv`](https://rstudio.github.io/renv/articles/renv.html) to manage package dependencies. Inside R (and with your working directory set correctly) run `renv::restore()`. This will install the correct versions of all the packages needed to replicate our results. Packages are installed in a stand-alone project library for this paper, and will not affect your installed R packages anywhere else. 

This project has a lot of package dependencies so depending on what you already have installed the `renv` process might take a while (like 10-20 minutes). 

Once you've successfully run `renv::restore()` you can reproduce our results by running sala-etal-food-reply.Rmd. This will knit the reply stored in sala-etal-food-reply.Rmd.


## Reproducing Results

The main results are produced by `sala_etal_reply.Rmd`. The Supplementary Information is produced by `sala_etal_reply_si.Rmd`. 

The analysis has a wide range of options. The core set used in the manuscript are set by the `params` section of each file's YAML section.

Running the full analysis requires two full sets of the results to be run, one with "pooled" and one with "local" density dependence. For convenience, we have included a wrapper script called `make_sala_etal_reply.R` that will run the entire analysis. However, be aware that running this script will likely take roughly 24 hours to complete. 


## References

Sala, E., Mayorga, J., Bradley, D., Cabral, R.B., Atwood, T.B., Auber, A., Cheung, W., Costello, C., Ferretti, F., Friedlander, A.M., Gaines, S.D., Garilao, C., Goodell, W., Halpern, B.S., Hinson, A., Kaschner, K., Kesner-Reyes, K., Leprieur, F., McGowan, J., Morgan, L.E., Mouillot, D., Palacios-Abrantes, J., Possingham, H.P., Rechberger, K.D., Worm, B., Lubchenco, J., 2021. Protecting the global ocean for biodiversity, food and climate. Nature 1–6. https://doi.org/10.1038/s41586-021-03371-z
