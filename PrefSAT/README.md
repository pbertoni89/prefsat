## SemOpt: Computing argumentation semantics as optimisation problem

### Licence
    SemOpt: Computing argumentation semantics as optimisation problem
    (Lite version)
    Copyright (C) 2012-2013  	Federico Cerutti <f.cerutti@abdn.ac.uk>
				Mauro Vallati <m.vallati@hud.ac.uk>

    Authors: Federico Cerutti <f.cerutti@abdn.ac.uk>
	     Mauro Vallati <m.vallati@hud.ac.uk>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 2 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

Glucose and Precosat are distributed under their own Licence.

GTest is distributed under its own Licence.

### Description

SemOpt uses SAT solvers for computing the semantics extensions on a
Dung's argumentation framework. Currently it works for preferred extensions only.

### Quick Start

#### Compiling

For building the Release version:

Open the eclipse project and compile with the Release Build Configuration

#### Running

#### Running
./SemOpt <inputfile.dl> <param1> ... <paramN>

-d 			 *HIGH* level of debug (very slow, very dense output)

-ExtSAT <satsolver> 	 uses as engine an external SAT Solver. Currently: GLUCOSE, PRECOSAT

-LabConds <num> 	 0 (default) -> C_1

 			 1 C_2

 			 2 C_3

 			 3 C_1^a

 			 4 C_1^b

 			 5 C_1^c

-sem <semantics> 	 Currently: complete, preferred, preferred-df, grounded, grounded-poly, stable, semistable

### Authors
Copyright holder: Federico Cerutti PhD <f.cerutti@abdn.ac.uk>, (c) 2013
