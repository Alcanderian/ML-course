#pragma once
#include "stdafx.h"


namespace nnet
{
  class optimizer
  {
  public:
    virtual mat optimize(const mat &g, const int &k) = 0;
  };


  class gradient_desc :
    public optimizer
  {
  public:
    mat optimize(const mat &g, const int &k) { return g; }
  };


  class adam :
    public optimizer
  {
  public:
    double beta;
    double gamma;
    double eps;
    mat first;
    mat second;
    adam(
      const double &beta = 0.9, 
      const double &gamma = 0.999, 
      const double &eps = 1e-8) :
      beta(beta), gamma(gamma), eps(eps)
    { }


    mat optimize(const mat &g, const int &k)
    {
      // init
      if (first.n_rows != g.n_rows || first.n_cols != g.n_cols)
        first = zeros(g.n_rows, g.n_cols), second = zeros(g.n_rows, g.n_cols);

      // s = beta * s + (1 - beta) * g
      first = beta * first + (1.0 - beta) * g;
      second = gamma * second + (1.0 - gamma) * square(g);

      // eta = sqrt(1 - gamma^k) / (1 - beta^k)
      double eta = sqrt(1 - pow(gamma, k)) / (1 - pow(beta, k));

      // g' = eta * s / (sqrt(r) + eps)
      return eta * first / (sqrt(second) + eps);
    }
  };
}