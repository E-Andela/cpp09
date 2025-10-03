CC = c++

FLAGS = -Wall -Wextra -Werror

TARGET = btc
SRC_DIR = src
SRC = $(SRC_DIR)/BitcoinExchange.cpp \
	$(SRC_DIR)/main.cpp

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re