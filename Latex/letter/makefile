fname=letter
TEX=pdflatex
BIB=biber
VIEWER=open -a preview
NCL=makeindex


all: $(fname).pdf

$(fname).pdf: $(fname).tex
	$(TEX) --synctex=1 $^

read:
	$(VIEWER) $(fname).pdf

clean:
	rm -f *.aux *.blg *.out *.bbl *.log *.nlo *.lof *.lot *.toc *.bcf *.ilg *.xml *.nls *.ind

cleanall: clean
	rm -f *.pdf


.PHONY: all pdf bib read clean cleanall
