# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/01 20:04:00 by ilmahjou          #+#    #+#              #
#    Updated: 2025/02/03 15:54:13 by ilmahjou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus

SRC_DIR = ./mandatory
BONUS_DIR = ./bonus
PRINTFDIR = ft-printf/
PRINTF = $(PRINTFDIR)libftprintf.a

SRC_SERVER = $(SRC_DIR)/server.c
SRC_CLIENT = $(SRC_DIR)/client.c
SRC_SERVER_B = $(BONUS_DIR)/server_bonus.c
SRC_CLIENT_B = $(BONUS_DIR)/client_bonus.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER_B = $(SRC_SERVER_B:.c=.o)
OBJ_CLIENT_B = $(SRC_CLIENT_B:.c=.o)

all: $(PRINTF) $(SERVER) $(CLIENT)

bonus: $(PRINTF) $(SERVER_BONUS) $(CLIENT_BONUS)

$(PRINTF):
	@$(MAKE) -C $(PRINTFDIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SERVER): $(OBJ_SERVER) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(SERVER) $(PRINTF)

$(CLIENT): $(OBJ_CLIENT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(CLIENT) $(PRINTF)

$(SERVER_BONUS): $(OBJ_SERVER_B) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ_SERVER_B) -o $(SERVER_BONUS) $(PRINTF)

$(CLIENT_BONUS): $(OBJ_CLIENT_B) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_B) -o $(CLIENT_BONUS) $(PRINTF)

clean:
	@$(MAKE) clean -C $(PRINTFDIR)
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_SERVER_B) $(OBJ_CLIENT_B)

fclean: clean
	@$(MAKE) fclean -C $(PRINTFDIR)
	rm -f $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re


