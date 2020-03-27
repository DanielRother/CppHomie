# gtest stuff
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
gmock_dep = gtest_proj.get_variable('gmock_dep')

tests_src = [
  'test_Dummy.cpp',
]  
e = executable(
  'testprog',
  tests_src,
  dependencies : [gtest_dep, gmock_dep],
  link_with : homie_lib,
)    
test('gtest tests', e)