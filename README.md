Vulkan Tutorial website code
============================

Tweaked by Tim Holt. Found at https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Base_code

I’m changing whatever I want as I go along, and using this opportunity to learn a lot about my chosen build tool as well (waf).

Also contains code for unit testing.

Because this is a personal exploration of Vulkan and other tools, the build script points to specific folders on my personal machine, and to a specific compiler (Visual Studio 2015, 64 bit). You may compile this project by changing library directory locations in the wscript file, making sure you have waf installed and in your PATH, and then running ‘waf-light configure build’ for the debug version, or ‘waf-light configure build_release’ for a release binary (a simple ‘waf-light’ or ‘waf-light build_release’ will re-compile). The required Vulkan dll is automatically copied to the build output folder, and must accompany the .exe.

This project is distributed under the MIT license, copyright 2016 Tim Holt, see LICENSE.txt for details.

doctest.h is copyright 2016 Viktor Kirilov, and is under the MIT license. It can be found at https://github.com/onqtam/doctest/ .

This project contains no licensed code from the waf project, but more information can be found at https://github.com/waf-project/waf .
