export RELVER := 1.7.0

release: prep psp lite pack clean
release_pr: prep psppr litepr pack clean

test-app:
	$(MAKE) -C tests/psp
	mkdir -p build/tempar-test
	cp tests/psp/EBOOT.PBP build/tempar-test/EBOOT.PBP

clean:
	rm -f src/*.elf
	rm -f src/*.prx
	rm -f src/objects/*.o
	rm -f src/languages/*.h
	rm -rf build/temp

prep:
	bin2c "src/languages/english.bin" "src/languages/english.h" "language_english"

pack:
	mkdir -p build/temp
	cp -r src/resources/* build/temp
	cp -r docs build/temp
	mv src/*.prx build/temp/seplugins/TempAR
	cd build/temp && tar cfvz ../tempar-$(RELVER).tar.gz *

psp:
	make -C src -f makefile_psp

lite:
	make -C src -f makefile_lite
	
psppr:
	make -C src -f makefile_psppr
	
litepr:
	make -C src -f makefile_litepr
