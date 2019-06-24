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

Notes on Code Conventions
=========================

## Regarding definition (.cpp) files:

### Function ordering

Local-only helper functions are forward declared immediately before the functions in which they are used, in the order they're used. Hint: it's a local-only helper iff it is global scope in a definition file, and it is not declared in any other file. Per-use forward declaration may involve multiple declarations of the same function.

Definitions are not (necessarily) in a strict order based on dependency, because evolving code changes the dependency order of function calls. However, all header-declared functions are defined before any local-only function definitions, and newly implemented functions will be defined somewhere after they are used, to at least roughly show "primacy".

New function definition placement will be based as close to per-level ordering as may be allowed without moving anything else around. (see https://en.wikipedia.org/wiki/Tree_(data_structure)#Per-level_ordering). I may occasionally re-order to strict per-level ordering in a commit made for that purpose, but shuffling code around in version-controlled code is a Very Bad Thing™. I'll only do it when I can no longer resist how beautifully logical such a strict ordering would be.

### Ugly Stuff

I'm also giving myself permission to do some truly ugly things in definition files, since ugly code can't hurt anyone from there. Using `using namespace std;` probably isn't too unusual for a definition file, but I'll probably only use it where I think it makes things clearer. I'll leave `std::` on std algorithms and some std containers, for example. What's less usual is some questionable macro usage, and whatever other weird crap I can come up with that I think makes actual definitions clearer, but would never be wise to put in a header.

### Using Statements

`using namespace std;`, of course, should NEVER EVER go in a header, but proper use in a definition file makes some things clearer. However, `using namespace` almost always carries side-effects. Using `using {namespace}::{identifier}` makes intentions and reasoning much clearer, and does not bring anything into scope that was not intended.

For some statements (e.g. anything in global scope, i.e. helper functions and local-only constants in definition files--or when it's a widely useful identifier with obvious meaning), it makes sense to put such using statements near the top of the file. Some using statements might make more sense placed in a local function/method definition. This will happen when it makes things clearer in one particular use, but not in every use everywhere in the file.

The widespread use of std::vector makes 'vector' without 'std::' unambiguous. 'begin()' and 'end()' are almost always used in contexts where it's obvious that they're generating an iterator, and 'string' is going to be a string class in any context, and whether it's even std::string is mostly moot in practice (though that's the usual assumption).

Something like std::set would probably be fine without the 'std::' prefix, but it's not used as often as something like 'vector', and it's also interpretable as a common English verb. Some std algorithms are obvious enough (like 'sort'), but there are a lot of them, and most people can't be expected to know them all. Even if the name of the algorithm makes its meaning obvious, emphasizing its connection to the STL gives the brain something to latch onto when trying to read the code. I still might indulge in a couple 'bare' std algorithms, like sort.

