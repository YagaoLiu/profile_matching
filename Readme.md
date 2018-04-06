Weighted Index
===

**Basic Instructions:**

No pre-installation is needed for this version.

The shell command 'make' should compile this program.

After compilation, the binary 'index' will be created in the working directory, e.g. you can call it in this directory via 
```
  ./index -t text.txt -z 8 -o output.txt
```
**Usage:**
```
Usage: index <options>
Standard (Mandatory):
	-t,	--text		<str>	Filename for the Weighted Sequence.
	-p,	--patterns	<str>	Filename for the Patterns.
	-o,	--output	<str>	Filename for Output.
	-z,	--threshold	<dbl>	Cumulative weighted threshold (Mandatory).
```
