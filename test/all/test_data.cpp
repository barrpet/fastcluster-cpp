#include "test.hpp"

#include "fastcluster.h"
#include "data.hpp"

#include <iostream>

TEST_CASE("karate data", "[karate]")
{
  KarateData d;
  const double* D = d.ds;
  MergeFC* mrg = fastcluster(d.nv, METHOD_METR_AVERAGE, D);
  
  const int* const m = mrg->merge();
  bool m_ok = true;
  for(unsigned i = 0; i < (d.nv-1)*2; i+=2)
  {
    INFO ( d.mg[i] <<  "  " << d.mg[i+1] << " : " << m[i/2] << "  " << m[(d.nv-1)+(i/2)] );
    CHECK( (m_ok &= ((d.mg[i] == m[i/2]) && (d.mg[i+1] == m[(d.nv-1)+(i/2)]))) );
  }
  REQUIRE( m_ok );
  
  const double* const h = mrg->height();
  bool h_ok = true;
  for(unsigned i = 0; i < d.nv-1; i++)
  {
    INFO( d.ht[i] << " : " << h[i] );
    CHECK( (h_ok &= (d.ht[i] == Approx( h[i] ).epsilon( 0.0001 ))) );
  }
  REQUIRE( h_ok );
  
  const int* const o = mrg->order();
  bool o_ok = true;
  for(unsigned i = 0; i < d.nv; i++)
  {
    INFO( d.od[i] << " : " << o[i] );
    CHECK( (o_ok &= (d.od[i] == o[i])) );
  }
  REQUIRE( o_ok );
  
  delete mrg;
}

