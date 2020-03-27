homie_header = [
  'Device.h',
  'HomieHelper.h',
  'Node.h',
  'PayloadDataTypes.h',
  'Utils/FileIOUtils.h',
]
homie_src = [
  'Device.cpp',
  'HomieHelper.cpp',
  'Node.cpp',
]

homie_lib = library('CppHomie',
           homie_src,
           install : true)

homie_dep = declare_dependency(link_with : homie_lib,
  include_directories : '.')