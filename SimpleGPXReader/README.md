Simple GPX Reader
=================

Read GXP File in a simple tree-like format.
Use SimpleGPXReader::parseData(QIODevice * data) to get a list of Trace, each contain a list of Segments, wich in turn contains a list of TracePoint.

Trace, Track and Segment are all of the type Node<subclass> to get as much code reuse as possible. However, they all inherit from Node_QT to get signal/slot abilities.

TODO: error raise an exception
TODO: Use namespace
TODO: Mixup with parseData : should return Trace.
