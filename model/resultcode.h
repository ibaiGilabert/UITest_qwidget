#ifndef RESULTCODE_H
#define RESULTCODE_H

#include <map>

namespace data_model {

/*!
 * \brief The ResultCode struct
 */
struct ResultCode {
  /*!
   * \brief The CodeValue enum
   */
  enum class CodeValue { kOk = 0, kOutOfTolerance = 42, kDefect = 43 };
  /*!
   * \brief The CodeType enum
   */
  enum class CodeType { kWarning, kError };

  /*!
   * \brief kResultCodes
   */
  static std::map<CodeValue, std::string> kResultCodes;

  /*!
   * \brief ResultCode
   */
  ResultCode(CodeValue, CodeType);

  /*!
   * \brief value_
   */
  CodeValue value_;
  /*!
   * \brief type_
   */
  CodeType type_;
};

}  // namespace data_model

#endif  // RESULTCODE_H
