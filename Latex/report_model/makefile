filename=main
TEX=pdflatex
BIB=biber
VIEWER=sumatrapdf 
NCL=makeindex

all: $(filename).pdf $(filename).bbl $(filename).nls


$(filename).pdf: $(filename).tex
	$(TEX) --synctex=1 $^

$(filename).bbl: $(filename).bcf 
	$(BIB) $^ --output-file $@ 

$(filename).nls: $(filename).nlo
	$(NCL) $^ -s nomencl.ist -o $@

link:
	$(TEX) --synctex=1 $(filename).tex
	$(TEX) --synctex=1 $(filename).tex
	$(TEX) --synctex=1 $(filename).tex

read:
	$(VIEWER) $(filename).pdf

clean:
	rm -f *.aux *.blg *.out *.bbl *.log *.nlo *.lof *.lot *.toc *.bcf *.ilg *.xml *.nls *.ind

cleanall: clean
	rm -f *.pdf


.PHONY: all pdf bib read clean cleanall
