/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitaabe <haitaabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:43:11 by haitaabe          #+#    #+#             */
/*   Updated: 2025/07/12 11:31:28 by haitaabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "../libft/libft.h"
#include <signal.h>
// #include "../include/minishell.h"

#define MAX_TOKENS 1024
#define TOKEN_BUF_SIZE 4096
typedef struct s_env t_env;

typedef struct s_tokenizer
{
	char	**tokens;
	char	**env_path;
	char	token_buf[4096];
	char	*word;
	char	*expanded;
	int		i;
	int		j;
	int		has_token;
	int		is_single;
	int		start;
	int		len;
}	t_tokenizer;


typedef enum e_token_type
{
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
    WORD
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    bool flags;
    struct s_token *next;
} t_token;

typedef struct s_cmd
{
    char **args;
    char *infile;
    char *outfile;
    int fd;
    int flags;
    int here_doc_fd;
    int append;
    char *heredoc_filename;
    int heredoc;
    int pipe_to_next;
    struct s_cmd *next;
} t_cmd;


// PARSING FUNCTIONS
 // entry point

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	*ft_malloc(size_t size, int mode);
char *ft_strncpy(char *dest, const char *src, unsigned int n);
char *ft_strcat(char *dest, const char *src);
int get_token_len(char *line, int i);
void	print_error2(const char *prefix, const char *name);

int is_space(int c);
int is_special(char c);
void skip_spaces(char *line, int *i);
t_token_type get_token_type(char *str);
char *extract_word(const char *input, int *i);
char *extract_special(const char *input, int *i);
char	*extract_quoted(const char *input, int *i, int *is_single ,t_token *type);
char *extract_var_name(const char *str, int *i);

t_cmd *new_cmd_node(void);
void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);
void add_arg(char ***args, char *new_arg);
void add_arg_to_cmd(t_cmd *cmd, char *arg);

void handle_redir(t_cmd *cmd, t_token **token);
void set_infile(t_cmd *cmd, char *redir, char *file);
void set_outfile(t_cmd *cmd, char *redir, char *file);

void free_tokens(char **tokens);
void free_command_list(t_cmd *cmds);
void free_cmds(t_cmd *head);

int	check_syntax_error(char **tokens ,t_token *type);

void print_cmds(t_cmd *cmds);

t_token *new_token(t_token_type type, char *value);
void add_token(t_token **head, t_token *new_token);
void free_token_list(t_token *tokens);

t_cmd *new_cmd_node(void);
void add_arg_to_cmd(t_cmd *cmd, char *arg);
void add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);

char *expand_variables(const char *input, char **envp, int exit_status, int split);

t_token_type get_token_type(char *str);

t_cmd *parse_tokens(t_token *tokens);
t_cmd *parse_tokens1(char **tokens, t_env *env,t_token *type);
t_token *tokenize_input(char *str,t_token *type);


char *ft_itoa_custom(int n);
char *strjoin_and_free(char *s1,const  char *s2);
char *strjoin_and_free_char(char *s1, char c);
int is_valid_var_char(char c);
char *extract_var_name(const char *input, int *i);

#endif