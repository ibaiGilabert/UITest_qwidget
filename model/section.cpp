#include "section.h"

namespace data_model {

/* Base Section */
unsigned int Section::GetLength() const { return length_; }

unsigned int Section::GetOD() const { return od_; }

void Section::SetLength(unsigned int length) { length_ = length; }

void Section::SetOD(unsigned int od) { od_ = od; }

/* Alpha*/
SectionAlpha::SectionAlpha(const std::vector<ResultCode> &c_dim,
                           const std::vector<ResultCode> &edge,
                           const std::vector<ResultCode> &defect)
    : Section(), c_dim_list_(c_dim), edge_list_(edge), defect_list_(defect) {}

void SectionAlpha::AddCDim(ResultCode result) { c_dim_list_.push_back(result); }

void SectionAlpha::AddEdge(ResultCode result) { edge_list_.push_back(result); }

void SectionAlpha::AddDefect(ResultCode result) {
  defect_list_.push_back(result);
}

size_t SectionAlpha::GetCDimListSize() const { return c_dim_list_.size(); }

size_t SectionAlpha::GetEdgeListSize() const { return edge_list_.size(); }

size_t SectionAlpha::GetDefectListSize() const { return defect_list_.size(); }

const ResultCode *SectionAlpha::GetCDimElement(unsigned int i) const {
  return (i >= c_dim_list_.size() ? nullptr : &c_dim_list_.at(i));
}

const ResultCode *SectionAlpha::GetEdgeElement(unsigned int i) const {
  return (i >= edge_list_.size() ? nullptr : &edge_list_.at(i));
}

const ResultCode *SectionAlpha::GetDefectElement(unsigned i) const {
  return (i >= defect_list_.size() ? nullptr : &defect_list_.at(i));
}

SectionAlpha::SectionType SectionAlpha::GetSectionType() const {
  return SectionType::kAlpha;
}

/* Beta */
SectionBeta::SectionBeta(float endurance, float elasticity)
    : Section(), endurance_(endurance), elasticity_(elasticity) {}

float SectionBeta::GetEndurance() const { return endurance_; }

float SectionBeta::GetElasticity() const { return elasticity_; }

SectionBeta::SectionType SectionBeta::GetSectionType() const {
  return SectionType::kBeta;
}

}  // namespace data_model
