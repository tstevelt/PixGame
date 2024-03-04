
PROG = PixGame
LIB = $(PROG).a
XLIB = /usr/local/lib64/weblib.a /usr/local/lib64/shslib.a
DEF = /usr/local/include

WEBDIR = /var/www/vhosts/silverhammersoftware/html
PRG =$(WEBDIR)/$(PROG).cgi

FILES = \
	$(LIB)(PixGame.o)			\
	$(LIB)(LoadImageArray.o)	\
	$(LIB)(GetInput.o)			\
	$(LIB)(ChkInput.o)			\
	$(LIB)(GeneratePicks.o)		\
	$(LIB)(ShufflePicks.o)		\
	$(LIB)(GameFuncs.o)			\
	$(LIB)(PaintTop.o)			\
	$(LIB)(PaintBig.o)			\
	$(LIB)(PaintLittle.o)		\
	$(LIB)(PaintDistract.o)		\
	$(LIB)(PaintBottom.o)		\
	$(LIB)(PaintEndGame.o)		\
	$(LIB)(LogGame.o)			\
	$(LIB)(ShowAll.o)

.SILENT:

$(PRG): $(LIB) $(XLIB)
	echo "using gcc to load $(PRG)"
	gcc -o $(PRG) $(LIB) $(XLIB)

$(LIB): $(FILES)

$(FILES): PixGame.h

jsmin:
	cat Distract.js  | jsmin > $(WEBDIR)/Distract.js
	ls -l $(WEBDIR)/Distract.js
	cat EndGame.js   | jsmin > $(WEBDIR)/EndGame.js
	ls -l $(WEBDIR)/EndGame.js
	cat Functions.js | jsmin > $(WEBDIR)/Functions.js
	ls -l $(WEBDIR)/Functions.js
	cat TouchMode.js | jsmin > $(WEBDIR)/TouchMode.js
	ls -l $(WEBDIR)/TouchMode.js

js:
	cp -pv Distract.js  $(WEBDIR)/Distract.js
	cp -pv EndGame.js   $(WEBDIR)/EndGame.js
	cp -pv Functions.js $(WEBDIR)/Functions.js
	cp -pv TouchMode.js $(WEBDIR)/TouchMode.js
	
greek:
	echo "Obfuscator https://codebeautify.org/javascript-obfuscator"
	cp -pv Distract.min.js  $(WEBDIR)/Distract.js
	cp -pv EndGame.min.js   $(WEBDIR)/EndGame.js
	cp -pv Functions.min.js $(WEBDIR)/Functions.js
	cp -pv TouchMode.min.js $(WEBDIR)/TouchMode.js
	
html:
	cp -pv PixGame.html $(WEBDIR)/PixGame.html

extra:
	cp -pv 100_5_letter.TXT $(WEBDIR)/100_5_letter.txt
	cp -pv 500_3plus.TXT $(WEBDIR)/500_3plus.txt
	cp -pv TestMenu.html $(WEBDIR)/TestMenu.html

clean:
	rm -f $(LIB)

all:
	make clean
	make
	make js
	make extra

.PRECIOUS: $(LIB)

