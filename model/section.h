#ifndef SECTION_H
#define SECTION_H

#include <memory>
#include <vector>

#include "resultcode.h"

namespace data_model {

class Section;
class SectionAlpha;
class SectionBeta;
/*!
 * \brief Adquisition
 */
typedef std::vector<std::unique_ptr<Section>> Adquisition;

/*!
 * \brief The Section class
 */
class Section {
 public:
  /*!
   * \brief The SectionType enum
   */
  enum class SectionType { kAlpha, kBeta };

  //  Section() = default;
  /*!
   * \brief ~Section
   * \return
   */
  virtual ~Section() = default;
  /*!
   * \brief GetLength
   * \return
   */
  inline unsigned int GetLength() const;
  /*!
   * \brief GetOD
   * \return
   */
  inline unsigned int GetOD() const;
  /*!
   * \brief GetSectionType
   * \return
   */
  virtual SectionType GetSectionType() const = 0;
  /*!
   * \brief SetLength
   */
  void SetLength(unsigned int);
  /*!
   * \brief SetOD
   */
  void SetOD(unsigned int);

 protected:
  /*!
   * \brief od_
   */
  unsigned int length_;
  /*!
   * \brief od_
   */
  unsigned int od_;
};

/*!
 * \brief The SectionAlpha class
 */
class SectionAlpha : public Section {
 public:
  /*!
   * \brief SectionAlpha
   */
  SectionAlpha(const std::vector<ResultCode> &, const std::vector<ResultCode> &,
               const std::vector<ResultCode> &);
  /*!
   * \brief ~SectionAlpha
   */
  ~SectionAlpha() = default;

  /*!
   * \brief GetSectionType
   * \return
   */
  SectionType GetSectionType() const override;
  /*!
   * \brief AddCDim
   */
  void AddCDim(ResultCode);
  /*!
   * \brief AddEdge
   */
  void AddEdge(ResultCode);
  /*!
   * \brief AddDefect
   */
  void AddDefect(ResultCode);

  /*!
   * \brief GetCDimListSize
   * \return
   */
  size_t GetCDimListSize() const;
  /*!
   * \brief GetEdgeListSize
   * \return
   */
  size_t GetEdgeListSize() const;
  /*!
   * \brief GetDefectListSize
   * \return
   */
  size_t GetDefectListSize() const;

  /*!
   * \brief GetCDimElement
   * \return
   */
  const ResultCode *GetCDimElement(unsigned int) const;
  /*!
   * \brief GetEdgeElement
   * \return
   */
  const ResultCode *GetEdgeElement(unsigned int) const;
  /*!
   * \brief GetDefectElement
   * \return
   */
  const ResultCode *GetDefectElement(unsigned int) const;

 private:
  /*!
   * \brief c_dim_list_
   */
  std::vector<ResultCode> c_dim_list_;
  /*!
   * \brief edge_list_
   */
  std::vector<ResultCode> edge_list_;
  /*!
   * \brief defect_list_
   */
  std::vector<ResultCode> defect_list_;
};

/*!
 * \brief The SectionBeta class
 */
class SectionBeta : public Section {
 public:
  /*!
   * \brief SectionBeta
   */
  SectionBeta(float, float);
  /*!
   * \brief ~SectionBeta
   */
  ~SectionBeta() = default;

  /*!
   * \brief GetEndurance
   * \return
   */
  float GetEndurance() const;
  /*!
   * \brief GetElasticity
   * \return
   */
  float GetElasticity() const;
  /*!
   * \brief GetSectionType
   * \return
   */
  SectionType GetSectionType() const override;

 private:
  /*!
   * \brief endurance_
   */
  float endurance_;
  /*!
   * \brief elasticity_
   */
  float elasticity_;
};

}  // namespace data_model

#endif  // SECTION_H
