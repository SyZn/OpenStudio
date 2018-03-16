/***********************************************************************************************************************
 *  OpenStudio(R), Copyright (c) 2008-2017, Alliance for Sustainable Energy, LLC. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *  following conditions are met:
 *
 *  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *  disclaimer.
 *
 *  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *  following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
 *  products derived from this software without specific prior written permission from the respective party.
 *
 *  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
 *  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
 *  specific prior written permission from Alliance for Sustainable Energy, LLC.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **********************************************************************************************************************/

#include "AirflowNetworkConstantPressureDrop.hpp"
#include "AirflowNetworkConstantPressureDrop_Impl.hpp"

#include <utilities/idd/IddEnums.hxx>
#include <utilities/idd/OS_AirflowNetworkConstantPressureDrop_FieldEnums.hxx>

#include "../utilities/units/Unit.hpp"

#include "../utilities/core/Assert.hpp"

namespace openstudio {
namespace model {

namespace detail {

  AirflowNetworkConstantPressureDrop_Impl::AirflowNetworkConstantPressureDrop_Impl(const IdfObject& idfObject,
                                                                                   Model_Impl* model,
                                                                                   bool keepHandle)
    : ModelObject_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == AirflowNetworkConstantPressureDrop::iddObjectType());
  }

  AirflowNetworkConstantPressureDrop_Impl::AirflowNetworkConstantPressureDrop_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                   Model_Impl* model,
                                                                                   bool keepHandle)
    : ModelObject_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == AirflowNetworkConstantPressureDrop::iddObjectType());
  }

  AirflowNetworkConstantPressureDrop_Impl::AirflowNetworkConstantPressureDrop_Impl(const AirflowNetworkConstantPressureDrop_Impl& other,
                                                                                   Model_Impl* model,
                                                                                   bool keepHandle)
    : ModelObject_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& AirflowNetworkConstantPressureDrop_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    return result;
  }

  IddObjectType AirflowNetworkConstantPressureDrop_Impl::iddObjectType() const
  {
    return AirflowNetworkConstantPressureDrop::iddObjectType();
  }

  double AirflowNetworkConstantPressureDrop_Impl::pressureDrop() const
  {
    boost::optional<double> value = getDouble(OS_AirflowNetworkConstantPressureDropFields::PressureDifferenceAcrosstheComponent,true);
    OS_ASSERT(value);
    return value.get();
  }

  bool AirflowNetworkConstantPressureDrop_Impl::setPressureDrop(double pressureDrop)
  {
    bool result = setDouble(OS_AirflowNetworkConstantPressureDropFields::PressureDifferenceAcrosstheComponent, pressureDrop);
    return result;
  }

} // detail

//AirflowNetworkConstantPressureDrop::AirflowNetworkConstantPressureDrop(const Model& model)
//  : ModelObject(AirflowNetworkConstantPressureDrop::iddObjectType(),model)
//{
//  OS_ASSERT(getImpl<detail::AirflowNetworkConstantPressureDrop_Impl>());
//}

AirflowNetworkConstantPressureDrop::AirflowNetworkConstantPressureDrop(const Model& model, double pressureDrop)
  : ModelObject(AirflowNetworkConstantPressureDrop::iddObjectType(), model)
{
  OS_ASSERT(getImpl<detail::AirflowNetworkConstantPressureDrop_Impl>());

  bool ok = setPressureDrop(pressureDrop);
  OS_ASSERT(ok);
}

IddObjectType AirflowNetworkConstantPressureDrop::iddObjectType() {
  return IddObjectType(IddObjectType::OS_AirflowNetworkConstantPressureDrop);
}

double AirflowNetworkConstantPressureDrop::pressureDrop() const {
  return getImpl<detail::AirflowNetworkConstantPressureDrop_Impl>()->pressureDrop();
}

bool AirflowNetworkConstantPressureDrop::setPressureDrop(double pressureDrop) {
  return getImpl<detail::AirflowNetworkConstantPressureDrop_Impl>()->setPressureDrop(pressureDrop);
}

/// @cond
AirflowNetworkConstantPressureDrop::AirflowNetworkConstantPressureDrop(std::shared_ptr<detail::AirflowNetworkConstantPressureDrop_Impl> impl)
  : ModelObject(impl)
{}
/// @endcond

} // model
} // openstudio

