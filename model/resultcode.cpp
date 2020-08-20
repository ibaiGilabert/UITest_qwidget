#include "resultcode.h"

namespace data_model {

std::map<ResultCode::CodeValue, std::string> ResultCode::kResultCodes = {
    {CodeValue::kOutOfTolerance,
     "CD Out of tolerance"},       /**< CD Out of tolerance */
    {CodeValue::kDefect, "Defect"} /**< Defect */
};
//////////////////////////////////

ResultCode::ResultCode(CodeValue value, CodeType type)
    : value_(value), type_(type) {}

}  // namespace data_model
