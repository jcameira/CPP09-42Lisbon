NAME 				= 	btc

CXX 				= 	c++
CXXFLAGS 			= 	-Wall -Wextra -Werror -g -std=c++98
IFLAGS				=	-I $(INCLUDES)
SANITIZE 			= 	--fsanitize=address
AR 					= 	ar rcs
RM 					= 	rm -rf

INCLUDES			=	includes/
DEFAULT_INCLUDES	=	-I /usr/local/includes

SRCS_PATH			=	srcs/
SRCS				=	BitcoinExchange.cpp main.cpp

OBJ_DIR 			= 	objects/
OBJS 				= 	$(SRCS:%.cpp=$(OBJ_DIR)%.o)
ALL_OBJECTS 		= 	$(OBJ_DIR)*.o

TOTAL_SRCS			=	$(words $(SRCS))
TOTAL_OBJS			=	$(words $(wildcard $(OBJ_DIR)*))
FILES				=	0

$(OBJ_DIR)%.o: 		$(SRCS_PATH)%.cpp
					@$(CXX) $(CXXFLAGS) $(IFLAGS) $(DEFAULT_INCLUDES) -c $< -o $@ && \
					$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
					$(call PRINT_PROGRESS,$(TOTAL_SRCS),$(GRN),$(YELLOW)Compiling$(DEFAULT) $@)

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS) 
					@$(CXX) $(CXXFLAGS) $(IFLAGS) $(ALL_OBJECTS) $(EXTRA_LIBS) -o $@
					@echo "\033[2F\033[0K$(CYAN)$@$(DEFAULT) successfully created\033[E"

sanitize:			$(OBJ_DIR) $(OBJS)
					@$(CXX) $(CXXFLAGS) $(SANITIZE) $(ALL_OBJECTS) -o $(NAME)
					@echo "\033[2F\033[0K$(CYAN)$(NAME)$(DEFAULT) successfully created\033[E"

$(OBJ_DIR):
					@mkdir -p $@

clean:				
					@$(foreach file,$(wildcard $(OBJ_DIR)*), \
						$(eval FILES=$(shell echo $$(($(FILES) + 1)))) \
						$(call PRINT_PROGRESS,$(TOTAL_OBJS),$(RED),$(YELLOW)Deleting$(DEFAULT) $(file)); \
						$(RM) $(file); \
					)
					@if [ -d "$(OBJ_DIR)" ]; then \
						$(RM) $(OBJ_DIR); \
						echo "\033[2F\033[0K$(PURPLE)$(OBJ_DIR)$(DEFAULT) deleted\033[E"; \
					fi
					$(eval FILES=0)

fclean:				clean
					@if [ -e "$(NAME)" ]; then \
						$(RM) $(NAME); \
						echo "$(PURPLE)$(NAME)$(DEFAULT) deleted"; \
					fi

re:					fclean all

.PHONY:				all sanitize clean fclean re

define PRINT_PROGRESS
    if [ "$(FILES)" -eq "1" ]; then \
        printf "\033[0K$(3)\n["; \
    else \
        printf "\033[0K\033[1F\033[0K$(3)\n["; \
    fi
    @for i in `seq 1 $(shell expr $(FILES) \* 70 / $(1))`; do \
        printf "$(2)=\033[0m"; \
    done
    @for i in `seq 1 $(shell expr 70 - $(FILES) \* 70 / $(1))`; do \
        printf " "; \
    done
    @printf "] $(shell echo $$(($(FILES) * 100 / $(1))))%%"
	if [ "$(FILES)" -eq "$(1)" ]; then \
        printf "\n"; \
	fi
endef

CYAN				=	\033[36m
PURPLE				=	\033[35m
YELLOW				=	\033[33m
GRN					=	\033[32m
RED					=	\033[31m
DEFAULT				=	\033[0m