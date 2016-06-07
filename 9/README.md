Done very loose in a short time.

Contents:
* tridiag.hpp --- matrix representation with a few helpers (header)
* tridia_aug.hpp --- augmented matrix (header)
* tridiag_detail.cpp and tridiag_aug_detail.cpp --- implementations of above templates
* tridiag-to-tex.cpp 
* doublesweep.cpp --- doublesweep-method solution
* instable.cpp --- implementation of instable algorithm described in task info
* tridiagsolve.cpp --- client for solving; redefine SOLVER to choose algo (td::instable or td::doublesweep)
* error.cpp --- given system of equations and correct answer, prints vector of abs deviations
* stats.cpp --- given degree $n$ of eqn system and number $k$ of needed trials,
                generates $k$ times $n$-degree tridiagonal diagonalizable linear equations system
                with their correct solutions,
                then solves with chosen algo and prints (in csv) deviation vectors for each trial
* edf.py --- given names of files printed by stats.cpp, merges samples and produces graph of edf of deviation
             (no analysis was done, maybe later i'll think of adjusting estimator and analyzing it's characteristics)
* stats_degree.py --- given names of files produced by stats.cpp,
                      shows a plot of dependence of deviation on degree of system

Notes:

`tridiagsolve` has `-v` option, that produces step-by-step solution for doublesweep method,
and outputs $y$ and $z$ vectors and $K$ coefficient for instable algo.

Most convenient way to browse the output is to postprocess it via pandoc:
`./tdsovl testname.{td,vec} | pandoc --latex-engine=xelatex -f latex - -so testname.pdf`
