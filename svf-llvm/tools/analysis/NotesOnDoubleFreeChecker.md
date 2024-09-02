# Starts at: virtual bool runOnModule(SVFIR* pag) override
- virtual function that overrides the corresponding leakchecker function.
- Why does this always return false?!

runOnModule calls analyze before returning false.

# void SrcSnkDDA::analyze(SVFModule* module)
- calls initialize on module
## initialize
### SVFIR* pag = PAG::getPAG();
- ( * SVF Intermediate representation, representing variables and statements as a Program Assignment Graph (PAG)
 * Variables as nodes and statements as edges.
 * SymID and NodeID are equal here (same numbering).)
### AndersenWaveDiff* ander = AndersenWaveDiff::createAndersenWaveDiff(pag);
- (/**
 * Wave propagation with diff points-to set.
 */)
### "Build Sparse Value-Flow Graph
### initSrcs();
- pure virtual class, implemented in LeakChecker?
### initSnks();
- pure virtual class, implemented in LeakChecker?

## ContextCond::setMaxCxtLen(Options::CxtLimit());
- Not relevant I think

# for (SVFGNodeSetIter iter = sourcesBegin(), eiter = sourcesEnd();
#            iter != eiter; ++iter)
- What is sourcesBegin()?: Litterly just returns .begin() of sources.
- What is sourcesEnd()?: Litterly just returns .end() of sources.
