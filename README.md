# CleanNulls

This formula plugin adds a CleanNulls function to Alteryx which converts string and text null values to their zero-value equivalent.  Strings are converted to an empty string ('') and numbers are converted to 0.

To see a working example, download and run the workflow in the AlteryxSample folder.
![CleanNulls function example](https://github.com/tlarsen7572/cleannulls/blob/master/AlteryxSample/Screenshot.PNG "CleanNulls function example")

### Installation

Download the pre-built binaries from the [releases page](https://github.com/tlarsen7572/cleannulls/releases) and follow the installation instructions provided.

### Why?

For string and numeric data, nulls are a redundant zero value.  Functionally, there is no difference between null and 0 or null and an empty string.  The presence of nulls complicates zero-value logic in our workflows and can be the source of insidious data prep errors.  In most cases, if not all, converting null values to their equivalent zero value reduces bugs and improves workflow clarity without removing informational value.

Before the CleanNulls function, the standard ways to remove nulls were `IF IsNull(x) THEN 0 ELSE x ENDIF` statements or the Data Cleansing tool.  Both of these methods have issues: The IF statements are very verbose and must be duplicated if you want to clean both numbers and strings while the Data Cleansing tool has poor performance on large data sets.  What was needed was a fast method which works on both numbers and strings without duplication.  The CleanNulls function is written in C++ and is very fast.  It also works across data types so a single function can be used on both string and number fields in a single Multi-Field Formula tool.
