filename2=presentation_model_2
filename1=presentation_model
TEX=pdflatex
BIB=biber
VIEWER=open -a preview
NCL=makeindex


all: $(filename1).pdf $(filename2).pdf

$(filename1).pdf: $(filename1).tex
	$(TEX) --synctex=1 $^


$(filename2).pdf: $(filename2).tex
	$(TEX) --synctex=1 $^

read:
	$(VIEWER) $(filename1).pdf
	$(VIEWER) $(filename2).pdf

clean:
	rm -f *.aux *.blg *.out *.bbl *.log *.nlo *.lof *.lot *.toc *.bcf *.ilg *.xml *.nls *.ind

cleanall: clean
	rm -f *.pdf


.PHONY: all pdf bib read clean cleanall
