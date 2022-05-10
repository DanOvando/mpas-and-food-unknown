#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector vpow(const NumericVector base, const NumericVector expo) {
  NumericVector out(base.size());
 
 for (int i = 0; i< base.size(); i++){
   
   out[i] = pow(base[i],expo[i]);
   
   }
 
  return out;
}


// [[Rcpp::export]]
NumericVector sim_mpa(NumericVector r, NumericVector k, NumericVector m, NumericVector u, NumericVector p_mpa,
                      int local_dd,int years, double phi, bool pt,
                      double plim) {
  
  
  int n = r.size();

  NumericVector mu(n,0.0);
  
  NumericVector yield(n,0.0);

  NumericVector hmpa(n,0.0);
  
  NumericVector inside_b(n,0.0);
  
  NumericVector last_inside_b(n,0.0);
  
  NumericVector outside_b(n,0.0);
  
  NumericVector last_outside_b(n,0.0);
  
  NumericVector growth_mult(n,1.0);
  
  NumericVector tmp(n,0.0);
  
  last_inside_b = k * p_mpa;
    
  last_outside_b = k * (1 - p_mpa);
  
  mu = m * (1 - p_mpa);
    
  for (int t = 0; t < years; t++){
    
    if (pt == 0){
    
    if (local_dd == 1){
      
      inside_b =
       last_inside_b +  r * last_inside_b * (1 - last_inside_b / (k * p_mpa)) - mu * (last_inside_b - (p_mpa / (1 - p_mpa)) * last_outside_b);
      
      outside_b =
       (1 - u) * last_outside_b +  r * last_outside_b * (1 - last_outside_b / (k * (1 - p_mpa))) + mu * (last_inside_b - (p_mpa / (1 - p_mpa)) * last_outside_b);
      
      last_inside_b = inside_b;
      
      last_outside_b = outside_b;
        
    } else {
      
      
      inside_b =
        last_inside_b +  p_mpa * r * (last_inside_b + last_outside_b)  * (1 - (last_inside_b + last_outside_b) / (k)) - mu * (last_inside_b - (p_mpa / (1 - p_mpa)) * last_outside_b);
      
      outside_b =
        (1 - u) * last_outside_b +  (1 - p_mpa) * r * (last_inside_b + last_outside_b) * (1 - (last_inside_b + last_outside_b) / (k)) + mu * (last_inside_b - (p_mpa / (1 - p_mpa)) * last_outside_b);
      
      last_inside_b = inside_b;
      
      last_outside_b = outside_b;
      
    
    } // close local dd ifelse
    
    } else {
      
      
      if (local_dd == 1){
        
        growth_mult =  last_inside_b / (plim * k * p_mpa);
        
        growth_mult[growth_mult > 1] = 1;
        
        // Rcpp::Rcout << "inside is " << last_inside_b << std::endl;
        inside_b =
          last_inside_b +  growth_mult * ((phi + 1) / phi) * r * last_inside_b * (1 - pow(last_inside_b / (k * p_mpa),phi)) - mu * (last_inside_b - (p_mpa / (1 - p_mpa)) * last_outside_b);
        
        inside_b[inside_b < 0] = 1e-6;
        
        
        // Rcpp::Rcout << "outside is " << last_outside_b << std::endl;
        
        growth_mult =  last_outside_b / (plim * k * (1  - p_mpa));
        // 
        growth_mult[growth_mult > 1] = 1;
        // 
        outside_b =
          (1 - u) * last_outside_b + growth_mult * ((phi + 1) / phi) * r * last_outside_b * (1 - pow(last_outside_b / (k * (1 - p_mpa)),phi)) + mu * (last_inside_b - (p_mpa / (1 - p_mpa)) * last_outside_b);
        
        outside_b[outside_b < 0] = 1e-6;
        
        last_inside_b = inside_b;
        
        last_outside_b = outside_b;
        
      } else {
        
        growth_mult =  (last_inside_b + last_outside_b) / (plim * k);
        
        growth_mult[growth_mult > 1] = 1;

        inside_b =
          last_inside_b +   growth_mult * ((phi + 1) / phi) * p_mpa * r * (last_inside_b + last_outside_b)  * (1 - pow((last_inside_b + last_outside_b) / (k),phi)) - mu * (last_inside_b - (p_mpa / (1 - p_mpa)) * last_outside_b);
        
        outside_b =
          (1 - u) * last_outside_b +  growth_mult * ((phi + 1) / phi) * (1 - p_mpa) * r * (last_inside_b + last_outside_b) * (1 - pow((last_inside_b + last_outside_b) / (k),phi)) + mu * (last_inside_b - (p_mpa / (1 - p_mpa)) * last_outside_b);
        
        last_inside_b = inside_b;
        
        last_outside_b = outside_b;
        
        
      } // close local dd ifelse
      
      
      
  
  } // close PT ifelse statement
 
 
  yield = u * outside_b;
 
  } // close years loop
  
  // return Rcpp::List::create(
  //   Rcpp::Named("inside_b") = inside_b,
  //   Rcpp::Named("outside_b") = outside_b,
  //   Rcpp::Named("yield") = yield,
  //   Rcpp::Named("growth_mult") = growth_mult
  // );

  return(yield);
  

}


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically 
// run after the compilation.
//

/*** R
# library(tidyverse)
# r <- 1
# 
# k <- 1000
# 
# m <- 0.9
# 
# p_mpa <- 1e-3
# 
# u <- 1 - exp(-r * 3)
# 
# years <- 10000
# 
# phi <- 0.188
# 
# pt <- 1
# 
# local_dd <- 1
# 
# plim <- 0.2
# 
# msy <- (r * k) / (phi + 1)^(1/phi)
# 
# p_mpa <- seq(1e-6,0.999, by = 0.01)
# out <- list()
# for (p in seq_along(p_mpa)){
#   
#   tmp <- sim_mpa(r,k,m,u,p_mpa[p],local_dd,years, phi, pt,plim)
#   
#   out[[p]] <- as.data.frame(tmp)
#   
# }
# 
# result <- tibble(p_mpa = p_mpa, out = out)
# 
# result <- result %>% 
#   unnest(cols = out)
# 
# result %>% 
#   select(p_mpa, inside_b, outside_b) %>% 
#   pivot_longer(contains("_b"), names_to = "location",values_to = "b") %>% 
#   ggplot(aes(p_mpa, b, color = location)) + 
#   geom_vline(aes(xintercept = 1 - plim)) +
#   geom_point()
# 
# result %>% 
#   select(p_mpa, yield) %>% 
#   ggplot(aes(p_mpa, yield / msy)) + 
#   geom_point()







*/
