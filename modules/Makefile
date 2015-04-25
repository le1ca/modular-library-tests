MODULES=$(shell find -type d -not -name '.' | awk '{print $$0 ".so"}')
CLEANDIRS=$(MODULES:.so=_clean)

all: $(MODULES)

./%.so: $(%:.so=) always_recurse
	make -C $(@:.so=)
	
clean: $(CLEANDIRS)
	
./%_clean: $(%:_clean=) always_recurse
	make -C $(@:_clean=) clean

always_recurse:
	@true
