.PHONY: clean All

All:
	@echo ----------Building project:[ memcached - Debug ]----------
	@"$(MAKE)" -f "memcached.mk"
clean:
	@echo ----------Cleaning project:[ memcached - Debug ]----------
	@"$(MAKE)" -f "memcached.mk" clean
