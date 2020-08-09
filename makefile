all: CodeTheoryDiploma

CodeTheoryDiploma: Main/source.o libs/libbound.so libs/libbase.so libs/libgenerate.so
	g++ -g -Llibs -lbase -lbound -lgenerate -o ctd Main/source.o

CodeTheoryDiplomaReusable: Main/init.o libs/libbound.so libs/libbase.so libs/libgenerate.so
	g++ -g -Llibs -lbase -lbound -lgenerate -o ctd_reusable Main/init.o

SystematicFormProvider: SystematicFormProvider/systematic.o libs/libbase.so
	g++ -g -Llibs -lbase -o get_systematic SystematicFormProvider/systematic.o

SystematicFormProvider/systematic.o: SystematicFormProvider/systematic.cpp
	g++ -g -fPIC -c SystematicFormProvider/systematic.cpp -o SystematicFormProvider/systematic.o

Main/init.o: Main/init.cpp
	g++ -g -c Main/init.cpp -o Main/init.o

Main/source.o: Main/source.cpp
	g++ -g -c Main/source.cpp -o Main/source.o

libs/libbound.so: BoundLibrary/bound.cpp
	g++ -g -fPIC -c BoundLibrary/bound.cpp -shared -o libs/libbound.so
	cp libs/libbound.so /usr/lib/libbound.so
	ldconfig

libs/libbase.so: BaseLibrary/base.cpp BaseLibrary/payload.cpp
	g++ -g -fPIC -c BaseLibrary/base.cpp -o BaseLibrary/base.o
	g++ -g -fPIC -c BaseLibrary/payload.cpp -o BaseLibrary/payload.o
	g++ -g -fPIC BaseLibrary/base.o BaseLibrary/payload.o -shared -o libs/libbase.so
	cp libs/libbase.so /usr/lib/libbase.so
	ldconfig
	#g++ -c BaseLibrary/base.cpp BaseLibrary/payload.cpp -shared -o libs/libbase.so

libs/libgenerate.so: GenerateLibrary/generate.cpp libs/libbase.so
	g++ -g -fPIC -Llibs -lbase -c GenerateLibrary/generate.cpp -shared -o libs/libgenerate.so
	cp libs/libgenerate.so /usr/lib/libgenerate.so
	ldconfig

clean: 
	rm Main/*.o ctd
	rm libs/*
	rm BaseLibrary/*.o
