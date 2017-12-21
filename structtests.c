#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum bools{FALSE = 0, TRUE = 1} boolean;

typedef struct		testing
{
	int			a;
	char			*string;
	boolean		options;
	struct testing	*next;
}				t_t;

void		z_z(t_t *s_pointer);
void		push(t_t **s_pointer);
void		add_end(t_t **s_pointer);
void		print(t_t *abc);

int main()
{
	t_t	*abc;
	char	copy[] = "1234567890";

	abc = (t_t*)malloc(sizeof(abc));
	printf("wheres the seg\n");
	abc->a = 10 * 4;
	abc->string = (char*)malloc(sizeof(char) * 10 + 1);
	abc->options = FALSE;
	abc->next = NULL;
	strcpy(abc->string, copy);
	printf("first values of the struct: %d, %s, %d\n", abc->a, abc->string, abc->options);
	z_z(abc);
	printf("second values of the struct: %d, %s, %d\n", abc->a, abc->string, abc->options);
	push(&abc);
	printf("are structures pushed 1: %d, %s, %d,\n    \t\t 2: %d, %s, %d\n", abc->a, abc->string, abc->options,
		abc->next->a, abc->next->string, abc->next->options);
	add_end(&abc);
	printf("existence? %s\n", abc->next->next->string);
	print(abc);
	printf("where are we currentlyl? %d, %s, %d\n", abc->a, abc->string, abc->options);
	return 0;
}
void		print(t_t *abc)
{
	while(abc != NULL)
	{
		printf("values of the struct: %d, %s, %d\n", abc->a, abc->string, abc->options);
		abc = abc->next;
	}
}
void		add_end(t_t **s_pointer)
{
	t_t	*newlist;
	t_t	*tmp;
	char	copy[] = "3rdstruct!";

	tmp = *s_pointer;
	newlist = (t_t*)malloc(sizeof(newlist));
	newlist->a = 10 * 6;
	newlist->string = (char*)malloc(sizeof(char) * 10 + 1);
	newlist->options = FALSE;
	newlist->next = NULL;
	strcpy(newlist->string, copy);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = newlist;
}
void		push(t_t **s_pointer)
{
	t_t	*newlist;
	//t_t	*tmp;
	char	copy[] = "abcdefghij";

	//tmp = *s_pointer;
	newlist = (t_t*)malloc(sizeof(newlist));
	newlist->a = 10 * 3;
	newlist->string = (char*)malloc(sizeof(char) * 10 + 1);
	newlist->options = TRUE;
	strcpy(newlist->string, copy);
	newlist->next = *s_pointer;
	*s_pointer = newlist;


}
void		z_z(t_t *s_pointer)
{
	//t_t *test;

	//test = *s_pointer;
	s_pointer->a = 10 * 5;
	s_pointer->string[0] = '5';
	s_pointer->string[1] = '5';
	s_pointer->string[2] = '5';
	s_pointer->options = TRUE;
}
