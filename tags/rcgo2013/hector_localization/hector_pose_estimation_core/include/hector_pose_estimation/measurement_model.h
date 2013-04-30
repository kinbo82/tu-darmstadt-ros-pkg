//=================================================================================================
// Copyright (c) 2011, Johannes Meyer and Martin Nowara, TU Darmstadt
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Flight Systems and Automatic Control group,
//       TU Darmstadt, nor the names of its contributors may be used to
//       endorse or promote products derived from this software without
//       specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//=================================================================================================

#ifndef HECTOR_POSE_ESTIMATION_MEASUREMENT_MODEL_H
#define HECTOR_POSE_ESTIMATION_MEASUREMENT_MODEL_H

#include <bfl/model/analyticmeasurementmodel_gaussianuncertainty.h>
#include <bfl/pdf/analyticconditionalgaussian_additivenoise.h>

#include <hector_pose_estimation/parameters.h>
#include <hector_pose_estimation/types.h>

#include <string>

namespace hector_pose_estimation {

class MeasurementModel : public BFL::AnalyticConditionalGaussianAdditiveNoise, public BFL::AnalyticMeasurementModelGaussianUncertainty {
public:
  MeasurementModel(unsigned int dimension, unsigned int conditional_arguments = 0);
  virtual ~MeasurementModel();

  virtual bool init() { return true; }
  virtual void cleanup() { }
  virtual void reset() { }

  virtual SystemStatus getStatusFlags() const { return SystemStatus(0); }
  virtual bool applyStatusMask(const SystemStatus& status) { return true; }

  ParameterList& parameters() { return parameters_; }
  const ParameterList& parameters() const { return parameters_; }

  virtual ColumnVector ExpectedValueGet() const = 0;
  virtual Matrix dfGet(unsigned int i) const = 0;

  using BFL::AnalyticConditionalGaussianAdditiveNoise::CovarianceGet;
  using BFL::AnalyticMeasurementModelGaussianUncertainty::CovarianceGet;

protected:
  ParameterList parameters_;
  const StateVector& x_;
  const ColumnVector& u_;
  mutable ColumnVector y_;
  mutable Matrix C_;
  mutable Matrix D_;
};

} // namespace hector_pose_estimation

#endif // HECTOR_POSE_ESTIMATION_MEASUREMENT_MODEL_H
