Vulkan Tutorial website code
============================

Tweaked by Tim Holt. Found at https://vulkan-tutorial.com/

A personal exploration of the vulkan tutorial by Alexander Overvoorde. I'm taking a few liberties, like adjusting the coding standard and using the vulkan.hpp header.

As of 2019-06-17, this codebase is being started over again from scratch after a ~3 year gap. I semi-refound the tutorial, started from the beginning, and decided I didn't want to have to go through the whole thing twice if I want to have a knowledge base based on the C++ interface for the API.

In most codebases, it probably doesn't make sense to start again in situ, especially when throwing basically everything away, but I like the idea of this repository serving as a record of my attempts and progress. Plus, I'm not generating the code myself, per se. Not to mention the old version was guaranteed never to get any use ever again.

As before, this project also serves as practice in other tools, like the doctest unit tester. This time, it also serves to help me learn Cmake and the clang toolset. Much of the clang functionality comes from Vim plugins, see my dot files at https://bitbucket.org/atimholt/dot_files/ .

Note that instead of using tags for each chapter's completed code, I'm just using commits with messages that start with "LESSON", followed by the lesson's page title (sometimes abbreviated with ellipses). That commit may or may not be the best rendering of the lesson into more sophisticated C++. You may find a better version between one LESSON commit and another.

The url for a given lesson (and sometimes headings within lessons) is found on a subsequent line of the "LESSON" commits' commit message.

This project is distributed under the MIT license, copyright 2016 and 2019 Tim Holt, see LICENSE.txt for details.

doctest.h is copyright 2016 Viktor Kirilov, and is under the MIT license. It can be found at https://github.com/onqtam/doctest/ .

This project contains no licensed code from the waf project, but more information can be found at https://github.com/waf-project/waf .
