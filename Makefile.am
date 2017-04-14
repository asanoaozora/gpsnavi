AUTOMAKE_OPTIONS = foreign
SUBDIRS = src
DIST_SUBDIRS = src

if ENABLE_AGL
CLEANFILES = agl/navigation.wgt flite jtalk
else
CLEANFILES = flite jtalk
endif

if ENABLE_AGL
bin_SCRIPTS = flite jtalk navigation.wgt
else
bin_SCRIPTS = flite jtalk
endif

flite: flite.in
	sed -e 's,[@]datadir[@],$(datadir),g' $(srcdir)/flite.in > flite
	chmod +x flite

jtalk: jtalk.in
	sed -e 's,[@]datadir[@],$(datadir),g' -e 's,[@]exec_prefix[@],$(exec_prefix),g' $(srcdir)/jtalk.in > jtalk
	chmod +x jtalk

navigation.wgt: src/navi
	rm -f agl/navigation.wgt
	mkdir -p agl
	cp src/.libs/navi agl/
	cp $(srcdir)/agl/config.xml agl/
	wgtpkg-pack -f -o navigation.wgt agl/
