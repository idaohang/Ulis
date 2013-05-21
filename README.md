Ulis
====

Ulis: A new GPS trace editor focused on simplicity

The main problem (for me) with trace files form GPS is the imprecision of the data. 
When you go at low speed (running), speed charts are jagged and it is hard to get the *correct* instantaneous speed.

The goal of this project is to correct the traces : remove incorrect points, smooth the paths. Minor editing options will be included.

To simplify the edition, the path is projected on a map (webview of Google maps).

This software use Qt, c++ (some c++11 extensions can be in use, tested on gcc/windows only)

Use case
--------

 - Automatically detect and remove outliers
 - Join tracks segments for long trips
 - Smooth the path (both speed and spatial data)
