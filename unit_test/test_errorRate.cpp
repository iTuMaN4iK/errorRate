#include <gtest/gtest.h>
#include "../errorRate.hpp"

TEST(getErrorRateIntervals, eq) {
  {
    Frames last{1000, 1};
    Frames next{2000, 501};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.5);
  }
  {
    Frames last{2000, 501};
    Frames next{3000, 1001};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.5);
  }
  {
    Frames last{3000, 1001};
    Frames next{4000, 1501};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.5);
  }
  {
    Frames last{4000, 1501};
    Frames next{5000, 2001};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.5);
  }
  {
    Frames last{5000, 2001};
    Frames next{25000, 2101};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.005);
  }
  {
    Frames last{25000, 2101};
    Frames next{45000, 2201};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.005);
  }
  {
    Frames last{2000, 501};
    Frames next{3000, 511};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.01);
  }
  {
    Frames last{3000, 511};
    Frames next{4000, 531};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.02);
  }
  {
    Frames last{4000, 531};
    Frames next{5000, 561};
    EXPECT_DOUBLE_EQ(getErrorRateIntervals(last, next), 0.03);
  }
}

TEST(getErrorRate, empty) {
  {
    ErrorRate er;
    EXPECT_EQ(er.getErrorRate(44), 0);
  }
}
TEST(getErrorRate, eq) {
  {
    ErrorRate er;
    er.setCurrent(0, {1000, 1});
    er.setCurrent(1, {2000, 501});
    er.setCurrent(2, {3000, 1001});
    er.setCurrent(3, {4000, 1501});
    er.setCurrent(4, {5000, 2001});
    er.setCurrent(24, {25000, 2101});
    er.setCurrent(44, {45000, 2201});
    EXPECT_DOUBLE_EQ(er.getErrorRate(44), 0.05);
  }
  {
    ErrorRate er;
    er.setCurrent(0, {1000, 1});
    EXPECT_DOUBLE_EQ(er.getErrorRate(), 0.001);
  }
  {
    ErrorRate er;
    er.setCurrent(0, {1000, 1});
    er.setCurrent(44, {5000, 2500});
    EXPECT_DOUBLE_EQ(er.getErrorRate(), 0.5);
  }
  {
    ErrorRate er;
    er.setCurrent(0, {1000, 1});
    er.setCurrent(1, {2000, 501});
    er.setCurrent(2, {3000, 1001});
    er.setCurrent(3, {4000, 1501});
    er.setCurrent(4, {5000, 2001});
    er.setCurrent(24, {25000, 2101});
    er.setCurrent(44, {45000, 2201});
    EXPECT_DOUBLE_EQ(er.getErrorRate(48), 0.05);
  }
  {
    ErrorRate er;
    er.setCurrent(0, {1000, 1});
    er.setCurrent(2, {2000, 501});
    er.setCurrent(4, {3000, 511});
    er.setCurrent(6, {4000, 531});
    er.setCurrent(8, {5000, 561});
    EXPECT_DOUBLE_EQ(er.getErrorRate(6), 0.02);
  }
  {
    ErrorRate er;
    er.setCurrent(0, {1000, 1});
    er.setCurrent(4, {3000, 511});
    er.setCurrent(6, {4000, 531});
    er.setCurrent(8, {5000, 561});
    EXPECT_DOUBLE_EQ(er.getErrorRate(6), 0.025);
  }
}