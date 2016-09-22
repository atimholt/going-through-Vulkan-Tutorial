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
	conf.setenv('debug')
	conf.env.MSVC_VERSIONS = ['msvc 14.0']
	conf.env.MSVC_TARGETS = ['x64']
	conf.env.CXXFLAGS = ['/nologo', '/EHsc', '/MD', '/DEBUG']
	conf.write_config_header('debug/config.hpp', remove=False)
	conf.load('compiler_cxx msvc')
	
	conf.setenv('release', env=conf.env.derive())
	conf.env.CXXFLAGS = ['/nologo', '/EHsc', '/MD']
	conf.define("DOCTEST_CONFIG_DISABLE", 1)
	conf.define("NDEBUG", 1)
	conf.write_config_header('release/config.hpp')
	# conf.load('compiler_cxx msvc')

def build(bld):
	if not bld.variant:
		bld.fatal('Call "waf-light build_debug" or "...build_release".')
	
	my_includes = ['.', # build directory, for generated config.hpp
	    'C:/development_resources/glm/',
	    'C:/development_resources/glfw-3.2.1.bin.WIN64/include/',
	    'C:/development_resources/VulkanSDK/1.0.26.0/Include/']
	
	my_libpath = [
	    'C:/development_resources/glfw-3.2.1.bin.WIN64/lib-vc2015/',
	    'C:/development_resources/VulkanSDK/1.0.26.0/Bin/']
	
	my_lib = ['vulkan-1', 'glfw3dll']
	
	my_source = ['src/main.cpp',
	    'src/ValidationLayer.cpp',
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
	dynamic_lib_local = os.path.abspath("./" + out + "/" + bld.variant + "/" + dynamic_lib_name)
	if not os.path.isfile(dynamic_lib_local):
		copyfile(my_dynamic_lib, dynamic_lib_local)

def init(ctx):
	from waflib.Build import BuildContext, CleanContext, InstallContext, UninstallContext
	
	for x in 'debug release'.split():
		for y in (BuildContext, CleanContext, InstallContext, UninstallContext):
			name = y.__name__.replace('Context','').lower()
			class tmp(y):
				cmd = name + '_' + x
				variant = x
	
	def buildall(ctx):
		import waflib.Options
		for x in ('build_debug', 'build_release'):
			waflib.Options.commands.insert(0, x)

# vim:set noet ts=4 sts=4 sw=4 ft=python:
