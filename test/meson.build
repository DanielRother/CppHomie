# gtest stuff
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

tests_src = [
    'test_Dummy.cpp',
    'test_Device.cpp',
    'test_Node.cpp',
    'test_PayloadDataTypes.cpp',
    'Utils/test_StringUtils.cpp',
]  
e = executable(
  'testprog',
  tests_src,
  include_directories: '../src',
  dependencies : [gtest_dep, gmock_dep, homie_dep],
)    
test('gtest tests', e)