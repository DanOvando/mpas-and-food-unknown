library(rmarkdown)
library(knitr)
library(here)

# Use this file to reproduce results
message("This takes a long time to run, like 24 hours. Go have a nice weekend outside.")



# summary of options ------------------------------------------------------

# In order to reproduce results from scratch, set all FALSE options to TRUE

#results_name  # name of folder to store results

#divide_stocks <- # load up prior stock division since it takes a while, TRUE recreate it

# run_regional_sala_etal <- # run regional resolution experiment

# run_global_sala_etal <- # run global sala et al. version experiment

# local_dd <- use local density dependence (1) or pooled (0)


# run base assumptions of local density dependence used in main paper
message("Starting base results with local density dependence")
rmarkdown::render(
  "sala_etal_reply.Rmd",
  params = list(
    results_name = "local_dd",
    divide_stocks = FALSE,
    run_regional_sala_etal = FALSE,
    run_global_sala_etal = FALSE,
    local_dd = 1
  ),
  output_file = here("results", "local_dd", "sala_etal_reply_local_dd.pdf")
)

message(
  "Finished based results with local density dependence, starting pooled density dependence"
)

# run alternative assumptions of pooled density dependence used in sensitivity analysis paper
rmarkdown::render(
  "sala_etal_reply.Rmd",
  params = list(
    results_name = "pooled_dd",
    divide_stocks = FALSE,
    run_regional_sala_etal = FALSE,
    run_global_sala_etal = FALSE,
    local_dd = 0
  ),
  output_file = here("results", "pooled_dd", "sala_etal_reply_pooled_dd.pdf")
)

# knit supporting information

message("Finished results, knitting Supplementary Information")

# run base assumptions of local density dependence used in main paper
rmarkdown::render(
  "sala_etal_reply_si.Rmd",
  output_file = here("results", "local_dd", "sala_etal_reply_si.pdf")
)

message("All done!")