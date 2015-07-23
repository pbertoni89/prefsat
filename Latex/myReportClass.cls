\NeedsTeXFormat{LaTeX2e}[1995/12/01]
\ProvidesPackage{myReportClass}[2008/02/13 v1.0 Tesi - DIA-Uniroma3]

\LoadClass[a4paper,11pt,oneside,italian]{memoir}

\RequirePackage[italian]{babel}
\RequirePackage{graphicx}
\RequirePackage{setspace}

% Pseudocode~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
%\usepackage{algpseudocode}
%\usepackage{algorithm}
\usepackage[boxed]{algorithm2e}
% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\usepackage[T1]{fontenc}
\usepackage[plainpages=false]{hyperref}
\hypersetup{ %rimuovere red box dai link. con miktex non serviva
    colorlinks,
    citecolor=black,
    filecolor=black,
    linkcolor=black,
    urlcolor=black
}
\usepackage{amsthm}	% per definizioni e teoremi
\usepackage{amsmath}	% per ``cases'' environment
\usepackage{amsfonts}  % per simbolo insieme reali
\usepackage{amssymb}	% math
\usepackage{xparse}    % intanto per varargs
\usepackage{float}     % per usare H nel figure env
%\usepackage{latexsym}
\usepackage{graphicx}
\usepackage{caption}	 % per figure in tabelle, math env in captions
%\usepackage{subcaption}%    "  "	
\usepackage{epstopdf}
%\usepackage[all]{hypcap}
\usepackage[utf8]{inputenc} % in teoria per usare accenti
\usepackage[T1]{fontenc}    %    "  "  "

% miei e/o scaricati!!!
\usepackage{stys/patlib}
\usepackage{stys/usecases}

% ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
\linespread{1.4}
\setlrmarginsandblock{3cm}{3cm}{*}
% profondità dell'indice (settato per stampare fino alle sottosezioni)
\setcounter{tocdepth}{1}
% numera parti, capitoli, sezioni, sottosezioni e sotto-sottosezioni
\maxsecnumdepth{subsubsection}
\setsecnumdepth{subsubsection}

% header personalizzati
\let\footruleskip\relax % for compatibility of memoir and fancyhdr
\let\rm\rmfamily        % for compatibility of memoir and blindtext (demo only)
\usepackage{fancyhdr}
\pagestyle{fancy}
\fancyhf{}
\addtolength{\headheight}{14pt}
\fancyhead[R]{\textbf{\thepage}}
\fancyhead[L]{\textbf{\leftmark}}