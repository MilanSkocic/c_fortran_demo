include make.in


all: lib tests examples


lib: $(LIB)

$(LIB):
	$(MAKE) -C src all

tests: $(TESTS)

$(TESTS):
	$(MAKE) -C tests all

runtests: $(TESTS)
	$(MAKE) -C tests run

examples: $(EXAMPLES)

$(EXAMPLES):
	$(MAKE) -C examples all

runexamples: $(EXAMPLES)
	$(MAKE) -C examples run


.PHONY: clean all cleanall doc docs

doc:
	$(MAKE) -C docs/doxygen all

docs:
	$(MAKE) -C docs/doxygen all

clean:
	$(MAKE) -C src clean
	$(MAKE) -C tests clean
	$(MAKE) -C examples clean
	$(MAKE) -C docs/doxygen clean


cleanall: clean
	$(MAKE) -C src cleanall
	$(MAKE) -C tests cleanall
	$(MAKE) -C examples cleanall
	$(MAKE) -C docs/doxygen cleanall
