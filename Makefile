.PHONY: upload run clean

all: upload

upload:
	pio run -t upload -e uno

run:
	pio run -t upload -t monitor -e uno

clean:
	rm -rf .pio
