# Changelog
## `0.0.6`
 - Require device argument on command line
 - Fix bug in command line where errors are overwritten by other errors
 - Compile tests against cmocka statically
 - Update Makefile
 - Add packet format documentation

## `0.0.5`
 - Improve code documentation
 - Add unit test for packet parsing
 - Add Travis CI integration
 - Update Makefile
 - Fix a crash when passing a device to `control`

## `0.0.4`
 - Improve Makefile
   - No longer removes obj files from the wrong directory
   - Now relies on a variable to name the binary
 - Update [ROADMAP](/ROADMAP.md)
 - Rewrite command line interface
   - Now uses `getopt`
   - Can now set the status of entire groups
 - Add debug serial endpoint
   - A real device is no longer needed to test functionality

## `0.0.3`
 - Update [ROADMAP](/ROADMAP.md) and [TODO](/TODO.md)
 - Change name of packet struct to lowercase

## `0.0.2`
 - Created [ROADMAP](/ROADMAP.md) and [CHANGELOG](/CHANGELOG.md) documents
 - Added license headers to Makefiles
 - Now using macros for platform dependant serial methods
 - Added `build` step to Makefiles (alias of `all` currently)
 - Now outputs version information with usage

## `0.0.1`
 - Initial release
