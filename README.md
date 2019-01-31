Analyser
========

Building:

Open the Xcode workspace `Analyser.xcworkspace` and hit Cmd-B to build.

There is a library part "LibAnalyser" and a front-end part, "AnalyserFE".

Locate the built executable by selecting `Project Navigator > AnalyserFE > Products > AnalyserFE` then right clicking and 'Show in Finder'.

Drop a test file into that directory. Call it 'infile'.

Running:

Run the Analyser with Cmd-R. It will pick up 'infile' and output a new file as 'outfile'.

That's it!

