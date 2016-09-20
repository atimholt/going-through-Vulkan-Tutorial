#! /usr/bin/env python

import os
import platform
from shutil import copyfile

# the following two variables are used by the target "waf dist"
VERSION='0.0.1'
APPNAME='Vulkan_project_template'

# these variables are mandatory ('/' are converted automatically)
top = '.'
out = 'build'

def options(opt):
	opt.load('compiler_cxx')

def configure(conf):
	conf.env.MSVC_VERSIONS = ['msvc 14.0']
	conf.env.MSVC_TARGETS = ['x64']
	conf.load('compiler_cxx msvc')
	
	if platform.system() == 'Windows':
		conf.env.CXXFLAGS = ['/nologo', '/EHsc', '/MD']

def build(bld):
	my_includes = [
	    'C:/development_resources/glm/',
	    'C:/development_resources/glfw-3.2.1.bin.WIN64/include/',
	    'C:/development_resources/VulkanSDK/1.0.26.0/Include/']
	
	my_libpath = [
	    'C:/development_resources/glfw-3.2.1.bin.WIN64/lib-vc2015/',
	    'C:/development_resources/VulkanSDK/1.0.26.0/Bin/']
	
	my_lib = ['vulkan-1', 'glfw3dll']
	
	my_source = ['src/main.cpp',
	    'src/HelloTriangleApplication.cpp']
	
	bld.program(
	    source    = my_source,
	    features  = 'cxx cxxprogram',
	    target    = 'vulkan_template',
	    libpath   = my_libpath,
	    lib       = my_lib,
	    includes  = my_includes,
	    )
	
	my_dynamic_lib = \
	    'C:/development_resources/glfw-3.2.1.bin.WIN64/lib-vc2015/glfw3.dll'
	
	dynamic_lib_name = os.path.split(my_dynamic_lib)[1]
	dynamic_lib_local = os.path.abspath("./" + out + "/" + dynamic_lib_name)
	if not os.path.isfile(dynamic_lib_local):
		copyfile(my_dynamic_lib, dynamic_lib_local)

# vim:set noet ts=4 sts=4 sw=4 ft=python:
