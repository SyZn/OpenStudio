/**********************************************************************
 *  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include "../ForwardTranslator.hpp"

#include "../../model/Model.hpp"
#include "../../model/OutputVariable.hpp"
#include "../../model/OutputVariable_Impl.hpp"
#include "../../model/OutputMeter.hpp"
#include "../../model/OutputMeter_Impl.hpp"
#include "../../model/Schedule.hpp"
#include "../../model/Schedule_Impl.hpp"
#include "../../model/EnergyManagementSystemOutputVariable.hpp"
#include "../../model/EnergyManagementSystemOutputVariable_Impl.hpp"


#include <utilities/idd/EnergyManagementSystem_OutputVariable_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

using namespace std;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateEnergyManagementSystemOutputVariable(EnergyManagementSystemOutputVariable & modelObject)
{
  boost::optional<std::string> m;
  boost::optional<std::string> s;

  IdfObject idfObject(openstudio::IddObjectType::EnergyManagementSystem_OutputVariable);
  m_idfObjects.push_back(idfObject);
  //Name
  s = modelObject.name();
  if (s) {
    idfObject.setName(*s);
  }
  s = modelObject.emsVariableName();
  if (s) {
    idfObject.setString(EnergyManagementSystem_OutputVariableFields::EMSVariableName, s.get());
  }
  s = modelObject.typeOfDataInVariable();
  if (s.is_initialized()) {
    idfObject.setString(EnergyManagementSystem_OutputVariableFields::TypeofDatainVariable, s.get());
  }
  s = modelObject.updateFrequency();
  if (s.is_initialized()){
    idfObject.setString(EnergyManagementSystem_OutputVariableFields::UpdateFrequency, s.get());
  }
  m = modelObject.emsProgramOrSubroutineName();
  if (m.is_initialized()) {
    idfObject.setString(EnergyManagementSystem_OutputVariableFields::EMSProgramorSubroutineName, m.get());
  }
  m = modelObject.units();
  if (m.is_initialized()) {
    idfObject.setString(EnergyManagementSystem_OutputVariableFields::Units, m.get());
  }
 
  return idfObject;
}

} // energyplus

} // openstudio
