# CrdtExamples

## Project Setup

### Git hook clang-format

This project uses `clang-format` for source formatting.
A git pre-commit hook verifies if the files being committed are formatted.

To install this hook :

```
$ cp hooks/pre-commit-clang-format .git/hooks/pre-commit
$ chmod +x .git/hooks/pre-commit
```

### Juce submodule

This project uses Juce as a build system.

To update the submodules :

```
$ git submodule init
$ git submodule update
```

To build introjucer for OSX (other plateform should be equivalent) :

```
$ xcodebuild -configuration Release -project "lib/JUCE/extras/Introjucer/Builds/MacOSX/The Introjucer.xcodeproj"
```

To generate solutions for OSX (other plateform should be equivalent) :
```
$ lib/JUCE/extras/Introjucer/Builds/MacOSX/build/Release/Introjucer.app/Contents/MacOS/Introjucer --resave CrdtExamples.jucer
$ open Builds/MacOSX/CrdtExamples.xcodeproj
```
