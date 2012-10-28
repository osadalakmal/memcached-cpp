.PHONY: clean All

All:
	@echo ----------Building project:[ memcached_test - Debug ]----------
	@cd "memcached_test" && "$(MAKE)" -f "memcached_test.mk"
clean:
	@echo ----------Cleaning project:[ memcached_test - Debug ]----------
	@cd "memcached_test" && "$(MAKE)" -f "memcached_test.mk" clean
