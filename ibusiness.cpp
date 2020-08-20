#include "ibusiness.h"

IBusiness::IBusiness(/*QObject* parent*/) /*: QObject(parent)*/ {}

const data_model::Adquisition* IBusiness::GetAdquisition() const {
  return &sections_;
}

size_t IBusiness::GetNumSection() const { return sections_.size(); }

const data_model::Section* IBusiness::GetSection(unsigned int i) const {
  return (i >= sections_.size() ? nullptr : sections_.at(i).get());
}
