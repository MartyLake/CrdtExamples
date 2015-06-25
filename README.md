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

