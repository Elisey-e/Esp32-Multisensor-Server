\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{astroedu-lab}[2021-07-26 AstroEdu Lab Problems Template, v1.0]
\LoadClass[a4paper, 12pt]{article}

% Characters and language
\RequirePackage{cmap}
\RequirePackage[utf8]{inputenc}
\RequirePackage[T2A, OT1]{fontenc}
\RequirePackage[russian]{babel}

% Geometry and spacing
\RequirePackage[margin=2cm]{geometry}
\RequirePackage{setspace}
	\setstretch{1.25}
\setlength{\parindent}{0ex}
\setlength{\parskip}{1ex plus .5ex minus .3ex}
\setlength{\skip\footins}{.5cm}

% Maths
\RequirePackage{mathtools}
	\mathtoolsset{showonlyrefs}
\RequirePackage[all,warning]{onlyamsmath}
    \AtBeginDocument{\catcode`\$=3}
\RequirePackage{mathrsfs}
\RequirePackage{cancel}
\RequirePackage{amssymb, wasysym}
\RequirePackage{icomma}

% Graphics
\RequirePackage{color}
\RequirePackage{graphicx}
\RequirePackage{float}
\RequirePackage{caption}
\RequirePackage{wrapfig}
	\setlength{\intextsep}{0pt}
\RequirePackage{tikz}
	\RequirePackage{tkz-euclide}
	\usetikzlibrary{calc}
	\usetikzlibrary{positioning}
\RequirePackage{pgfplots}
    \pgfplotsset{compat=newest}

% Tables
\RequirePackage{booktabs}
\RequirePackage{array}
\RequirePackage{multirow}
\RequirePackage{dcolumn}
    \newcolumntype{d}[1]{D{.}{.}{#1}}
\RequirePackage{tablefootnote}
\RequirePackage{longtable}

% Lists
\RequirePackage{enumitem}
	\setlist[enumerate]
	   {label=(\alph*),
		leftmargin=!,
		topsep=0mm,
		itemsep=0mm,
		labelsep=2ex}

% Hyphenation
\pretolerance=9999
\tolerance=9999
\hyphenpenalty=9999
\emergencystretch=2cm

% Fonts and style
\RequirePackage{paratype, newpxmath}
\pagestyle{empty}

% Class-specific definitions
\newenvironment{problem}[1]
	{\paragraph{#1}~\\[.33\parskip]}
	{\clearpage}
\newenvironment{solution}
	{\paragraph{\it Решение.}}
	{}
\newenvironment{answer}
	{\paragraph{\it Ответ:}}
	{}
\newenvironment{answer*}
	{\paragraph{\it Ответы:}}
	{}
