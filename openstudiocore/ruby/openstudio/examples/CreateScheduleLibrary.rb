########################################################################################################################
#  OpenStudio(R), Copyright (c) 2008-2016, Alliance for Sustainable Energy, LLC. All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
#  following conditions are met:
#
#  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
#  disclaimer.
#
#  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
#  following disclaimer in the documentation and/or other materials provided with the distribution.
#
#  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote
#  products derived from this software without specific prior written permission from the respective party.
#
#  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative
#  works may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without
#  specific prior written permission from Alliance for Sustainable Energy, LLC.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
#  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER, THE UNITED STATES GOVERNMENT, OR ANY CONTRIBUTORS BE LIABLE FOR
#  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
#  AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
#  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
########################################################################################################################

######################################################################
# == Synopsis 
#
#   Seed a local building component library with all of the schedules
#   in an OpenStudio Model file.
#
# == Usage
#
#  ruby CreateScheduleLibrary.rb ARGV[0] ARGV[1]
#
#  ARGV[0] - Path to OpenStudio Model (osm) file.
#  ARGV[1] - optional - Path location for project database.
#
# == Examples
#
#   ruby CreateScheduleLibrary.rb 'C:\path\to\osm\filename.osm' 'C:\my\database\location\filename'
#
######################################################################

require 'openstudio'

# load osm file
osmFilepath = OpenStudio::Path.new(ARGV[0])
oModel = OpenStudio::Model::Model.load(osmFilepath)
if oModel.empty?
  raise "Unable to load OpenStudio Model from path " + osmFilepath.to_s + "."
end
model = oModel.get

# create database
projectFilepath = OpenStudio::Path.new("./scheduleLibrary.osp")
if ARGV.size > 1
  projectFilepath = OpenStudio::Path.new(ARGV[1])
end
runmanagerFilepath = projectFilepath.parent_path() / 
    OpenStudio::Path.new(OpenStudio::toString(projectFilepath.stem()) + "-run.db")
puts projectFilepath
puts runmanagerFilepath
OpenStudio::remove(projectFilepath) if OpenStudio::exists(projectFilepath)   
OpenStudio::remove(runmanagerFilepath) if OpenStudio::exists(runmanagerFilepath) 
runmanager = OpenStudio::Runmanager::RunManager.new(runmanagerFilepath,true)
database = OpenStudio::Project::ProjectDatabase.new(projectFilepath,runmanager)

# create schedule components
schedules = model.getSchedules
puts "Creating components for " + schedules.size.to_s + " schedules."
components = OpenStudio::Model::ComponentVector.new
schedules.each { |schedule|
  newComponent = schedule.createComponent
  ok = newComponent.componentData.setName(schedule.name.get)
  raise "Unable to set Component name to '" + schedule.name.get + "'." if not ok
  components.push(newComponent)
}



# save components to database
index = 1
puts "Saving " + components.size.to_s + " components to " + projectFilepath.to_s + "."
components.each { |component|
  puts "Begin saving component #{index}"
  path = projectFilepath.parent_path() / OpenStudio::Path.new("component" + index.to_s)
  puts "Component dir = #{path}"
  OpenStudio::remove_all(path) if OpenStudio::exists(path)
  path = path / OpenStudio::Path.new("component.osc")
  puts "Component path = #{path}"
  component.save(path,true)
  fileReference = OpenStudio::FileReference.new(path)
  fileReferenceRecord = OpenStudio::Project::FileReferenceRecord.new(fileReference,database)
  index = index + 1
}

database.save