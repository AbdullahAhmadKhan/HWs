LDFLAGS=-std=c++11
MAKER=make --no-print-directory
DIFFER=diff -y --color --minimal --suppress-common-lines

define check_class
	@$(MAKER) clean;
	@echo "compiling $(1)";
	@if $(MAKER) $(1); then \
		echo "$(1) compiled successfully.\nchecking outputs"; \
	else\
		echo "we cannot work with a non-compiled file"; exit 1; \
	fi
	@$(MAKER) run | $(DIFFER) example_$(1).txt -;
	@echo "$(1) passed";
endef

transaction: ; @g++ $(LDFLAGS) transaction_test.cpp Transaction.cpp -ggdb3 -o Test
account: ; @g++ $(LDFLAGS) account_test.cpp Transaction.cpp Account.cpp -ggdb3 -o Test
bank: ; @g++ $(LDFLAGS) bank_test.cpp Transaction.cpp Account.cpp Bank.cpp -ggdb3 -o Test
run: ;./Test
valgrind: ; @valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./Test
clean: ; @rm -rf Test
check:
	$(call check_class,transaction)
	$(call check_class,account)
	$(call check_class,bank)