#include "test.hpp"

#include "fastcluster.h"

bool merge_nullptrs(const MergeFC& m)
{
  return m.merge() == FC_NULLPTR &&
         m.height() == FC_NULLPTR &&
         m.order() == FC_NULLPTR;
}

bool merge_alloc(const MergeFC& m)
{
  return m.merge() != FC_NULLPTR &&
         m.height() != FC_NULLPTR &&
         m.order() != FC_NULLPTR;
}

TEST_CASE("merge constructors", "[merge]")
{
  SECTION("default ctor")
  {
    MergeFC m0;
    REQUIRE( m0.get_n() == m0.size() );
    REQUIRE( m0.size() == 0 );
    REQUIRE( merge_nullptrs(m0) );
  }

  SECTION("ctor(5)")
  {
    MergeFC m1(5);
    REQUIRE( m1.size() == 5 );
    REQUIRE( merge_alloc(m1) );
  }

  SECTION("ctor(11000)")
  {
    MergeFC m2(11000);
    REQUIRE( m2.get_n() == 11000 );
    REQUIRE( merge_alloc(m2) );
  }
}

TEST_CASE("merge resizing (free/init)", "[merge]")
{
  MergeFC m0(100);
  REQUIRE( m0.get_n() == 100 );
  REQUIRE( merge_alloc(m0) );

  SECTION("free after sized")
  {
    m0.free();
    REQUIRE( m0.get_n() == 0 );
    REQUIRE( merge_nullptrs(m0) );

    SECTION("init after free to 0")
    {
      m0.init(0);
      REQUIRE( m0.get_n() == 0 );
      REQUIRE( merge_nullptrs(m0) );
    }

    SECTION("init after free to 50")
    {
      m0.init(50);
      REQUIRE( m0.get_n() == 50 );
      REQUIRE( merge_alloc(m0) );
    }

    SECTION("free after freed")
    {
      m0.free();
      REQUIRE( m0.get_n() == 0 );
      REQUIRE( merge_nullptrs(m0) );
    }
  }

  SECTION("init after sized")
  {
    SECTION("init twice the size")
    {
      t_index sz = m0.size() * 2;
      m0.init(sz);
      REQUIRE( m0.get_n() == sz );
      REQUIRE( merge_alloc(m0) );
    }

    SECTION("init half the size")
    {
      t_index sz = m0.size() / 2;
      m0.init(sz);
      REQUIRE( m0.get_n() == sz );
      REQUIRE( merge_alloc(m0) );
    }

    SECTION("init same size")
    {
      t_index sz = m0.size();
      const t_index* mrg = m0.merge();
      const t_float* hgt = m0.height();
      const t_index* odr = m0.order();

      m0.init(sz);
      REQUIRE( m0.get_n() == sz );
      REQUIRE( merge_alloc(m0) );
      REQUIRE( m0.merge() == mrg );
      REQUIRE( m0.height() == hgt );
      REQUIRE( m0.order() == odr );
    }
  }
}


TEST_CASE("merge free", "[merge]")
{
  MergeFC m0(100);
  REQUIRE( m0.get_n() == 100 );
  REQUIRE( merge_alloc(m0) );

  MergeFC m1;
  CAPTURE( m1.size() );
  REQUIRE( m1.size() == 0 );
  REQUIRE( merge_nullptrs(m1) );

  SECTION("default ctor then free")
  {
    m1.free();
    REQUIRE( m1.size() == 0 );
    REQUIRE( merge_nullptrs(m1) );
  }

  SECTION("ctor(100) then free")
  {
    m0.free();
    REQUIRE( m0.get_n() == 0 );
    REQUIRE( merge_nullptrs(m0) );
  }
}

TEST_CASE("merge other", "[merge]")
{
  MergeFC m0;

  SECTION("assign from temp rvalue")
  {
    m0 = MergeFC(20);
    REQUIRE( m0.get_n() == 20 );
    REQUIRE( merge_alloc(m0) );

    MergeFC m1 = MergeFC(10);
    REQUIRE( m1.get_n() == 10 );
    REQUIRE( merge_alloc(m1) );
  }
}
