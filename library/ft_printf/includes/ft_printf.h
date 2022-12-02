/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minseok2 <minseok2@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:07:23 by minseok2          #+#    #+#             */
/*   Updated: 2022/11/05 11:05:35 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>

//define flags bit mask
# define ZERO					1
# define PLUS					2
# define SPACE					4
# define LEFT					8
# define HASH					16
# define PRECISION				32

//define status
# define ERROR					-1
# define START					0
# define PARSE_FLAG				1
# define PARSE_WIDTH			2
# define PARSE_PRECISION		3
# define BRANCH_TYPE			4
# define END					5

//define common inner status
# define SET_TOTAL_LEN			10
# define END_PRINT				0

//define %c inner status
# define SET_CHARACTER_LOCATION	20
# define PRINT_C				21

//define %s inner status
# define PRECISING_STRING		30
# define SET_STRING_LOCATION	31
# define PRINT_S				32

//define %p inner status
# define SET_ADDRESS_LOCATION	40
# define PRINT_P				41

//define %d and %i inner status
# define PRECISING_NUM			50
# define COMBINE_PARTS			51
# define PRINT_DI				52

//define %u inner status
# define PRECISING_U_NUM		60
# define SET_U_NUM_LOCATION		61
# define PRINT_U				62

//define branch_xX function option
# define LOWER					70
# define UPPER					71

//define %x and %X inner status
# define PRECISING_HEX_NUM		80
# define COMBINE_HEX_PARTS		81
# define PRINT_X				82

typedef struct s_info
{
	int				status;
	const char		*format;
	va_list			args;
	int				total_len;
	unsigned char	flags;
	int				width;
	int				precision;
}	t_info;

typedef struct s_num_info
{
	int		num;
	char	*num_string;
	int		num_string_len;
}	t_num_info;

typedef struct s_address_info
{
	uintptr_t	address;
	char		*address_string;
	int			address_string_len;
}	t_address_info;

typedef struct s_u_num_info
{
	unsigned int	u_num;
	char			*u_num_string;
	int				u_num_string_len;
}	t_u_num_info;

typedef struct s_hex_num_info
{
	unsigned int	hex_num;
	char			*hex_num_string;
	int				hex_num_string_len;
}	t_hex_num_info;

//ft_printf.c
void	init_info(t_info *info);
int		ft_printf(const char *format, ...);

//libft_functions.c
size_t	ft_pf_strlen(const char *s);
void	*ft_pf_memset(void *b, int c, size_t len);
void	*ft_pf_memmove(void *dst, const void *src, size_t len);
char	*ft_pf_strdup(t_info *info, const char *s1);

//string_util_functions.c
void	do_write(t_info *info, const char *input, int total_len);
void	print_string(t_info *info, int *printed_len);

//judgement_functions.c
int		is_flag(char character);
int		is_numeric(char character);
int		is_precision(char character);

//parse_functions.c
void	parse_flag(t_info *info);
void	parse_width(t_info *info);
void	parse_precision(t_info *info);

//branch_type.c
void	branch_type(t_info *info, int *printed_len);

//branch_c.c
void	branch_c(t_info *info, int *printed_len, char character);

//branch_s.c
void	branch_s(t_info *info, int *printed_len, char *string);

//branch_di.c
void	branch_di(t_info *info, int *printed_len, int number);

//branch_di_util1.c
void	init_num_info(t_info *info, t_num_info *num_info, int number);

//branch_di_util2.c
void	set_total_len_di(t_info *info, t_num_info *num_info, \
		char **output_di);

//branch_di_util3.c
void	combine_parts(t_info *info, t_num_info *num_info, char *output_di);

//branch_p.c
void	branch_p(t_info *info, int *printed_len, uintptr_t address);

//branch_p_util1.c
void	init_address_info(t_info *info, t_address_info *address_info, \
		uintptr_t address);

//branch_u.c
void	branch_u(t_info *info, int *printed_len, unsigned int u_number);

//branch_u_util1.c
void	init_u_num_info(t_info *info, t_u_num_info *u_num_info, \
		unsigned int u_number);

//branch_u_util2.c
void	set_total_len_u(t_info *info, t_u_num_info *u_num_info, \
		char **output_u);

//branch_x.c
void	branch_x(t_info *info, int *printed_len, unsigned int hex_number, \
		int OPTINE);

//branch_x_util1.c
void	init_hex_num_info(t_info *info, t_hex_num_info *hex_num_info, \
		unsigned int hex_number, int OPTINE);

//branch_x_util2.c
void	set_total_len_x(t_info *info, t_hex_num_info *hex_num_info, \
		char **output_x);

//branch_x_util3.c
void	combine_hex_parts(t_info *info, t_hex_num_info *hex_num_info, \
		char *output_x, int option);

#endif
