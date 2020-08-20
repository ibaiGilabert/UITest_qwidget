#ifndef MOCKBUSINESS_H
#define MOCKBUSINESS_H

#include "ibusiness.h"

class MockBusiness : public IBusiness {
 public:
  explicit MockBusiness() = default;
  ~MockBusiness() override = default;

  void ProcessNewAdquisition() override;
};

#endif  // MOCKBUSINESS_H
