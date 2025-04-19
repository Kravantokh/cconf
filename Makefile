CC=cc

.PHONY: all
all: configure apply_configuration manage_packages

.PHONY: configure
configure: 
	@echo "Compiling configuration.c"
	$(CC) configuration.c -o configure

.PHONY: apply_configuration
apply_configuration:
	@echo "Running compiled configurer."
	./configure

.PHONY: manage_packages
manage_packages:
	@echo "Running package management script."
	chmod +x ./manage_packages.sh
	./manage_packages.sh

