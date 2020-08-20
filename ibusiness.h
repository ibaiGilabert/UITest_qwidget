#ifndef IBUSINESS_H
#define IBUSINESS_H

#include "model/section.h"

/*!
 * \brief The IBusiness class
 */
class IBusiness {
 public:
  /*!
   * \brief ~IBusiness
   * \return
   */
  virtual ~IBusiness() = default;

  /*!
   * \brief GetNumSection
   * \return
   */
  size_t GetNumSection() const;
  /*!
   * \brief GetAdquisition
   * \return
   */
  const data_model::Adquisition* GetAdquisition() const;
  /*!
   * \brief GetSection
   * \return
   */
  const data_model::Section* GetSection(unsigned int) const;

  /*!
   * \brief ProcessNewAdquisition
   */
  virtual void ProcessNewAdquisition() = 0;

 protected:
  /*!
   * \brief IBusiness
   */
  explicit IBusiness();

 protected:
  /*!
   * \brief sections_
   */
  data_model::Adquisition sections_;
};

#endif  // IBUSINESS_H
