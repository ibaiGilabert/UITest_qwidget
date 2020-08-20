#include "mockbusiness.h"

//#include <iostream>

void MockBusiness::ProcessNewAdquisition() {
  // Fill some mocking sections

  const int repeater = 20;
  sections_ = std::vector<std::unique_ptr<data_model::Section>>(2 * repeater);

  for (unsigned int i = 0; i < repeater; ++i) {
    // fill n-1 elements with alpha sections
    {  // #0
      std::unique_ptr<data_model::SectionAlpha> alpha =
          std::make_unique<data_model::SectionAlpha>(
              data_model::SectionAlpha({}, {}, {}));
      alpha->SetOD(28);
      alpha->SetLength(150);
      // C.Dim
      alpha->AddCDim(data_model::ResultCode(
          data_model::ResultCode::CodeValue::kOutOfTolerance,
          data_model::ResultCode::CodeType::kWarning));
      alpha->AddCDim(data_model::ResultCode(
          data_model::ResultCode::CodeValue::kOutOfTolerance,
          data_model::ResultCode::CodeType::kError));

      // Edge Ok!

      // Defect
      alpha->AddDefect(
          data_model::ResultCode(data_model::ResultCode::CodeValue::kDefect,
                                 data_model::ResultCode::CodeType::kError));
      sections_[2 * i] = std::move(alpha);
    }
    // the last one is a Beta section
    {  // #1

      std::unique_ptr<data_model::SectionBeta> beta =
          std::make_unique<data_model::SectionBeta>(
              data_model::SectionBeta(0.8, 0.25));
      beta->SetOD(28);
      beta->SetLength(150);
      sections_[2 * i + 1] = std::move(beta);
    }
  }
}
