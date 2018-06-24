#FILL THIS IN
HDIPATH=/home/exa/work/hdi-install

CXXFLAGS=-I$(HDIPATH)/include
HDILIBPATH=$(HDIPATH)/bin/hdi
HDILIBS= \
	$(HDILIBPATH)/libhdidimensionalityreduction.a \
	$(HDILIBPATH)/libhdidata.a \
	$(HDILIBPATH)/libhdiutils.a \


OBJECTS=asne.cpp.o

#TODO this is bad, R CMD COMPILE can't pass thruogh the include path, which
#sucks. Copying the whole command from that sucks equivalently, but at least
#works.
%.cpp.o: %.cpp
	g++  -I"/usr/share/R/include" -DNDEBUG -fpic  -g -O2 -fdebug-prefix-map=/build/r-base-3.5.0=. -fstack-protector-strong -Wformat -Werror=format-security -Wdate-time -D_FORTIFY_SOURCE=2 -g  -c $< -o $@ $(CXXFLAGS)

#same shit once again
asne.so: $(OBJECTS)
	gcc -std=gnu99 -shared -L/usr/lib/R/lib -Wl,-z,relro -o asne.so $(OBJECTS) $(HDILIBS) -lflann_cpp
