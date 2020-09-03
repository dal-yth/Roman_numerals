#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
** Prints usage
*/

void	print_usage(void)
{
	printf("Usage: ./romans MDCLXVI\n");
	exit(0);
}

/*
** Various error messages
*/

void	print_error(int err)
{
	if (err == 0)
		dprintf(2, "Error: Malloc error\n");
	else if (err == 1)
		dprintf(2, "Error: Incorrect character\n");
	else if (err == 2)
		dprintf(2, "Error: Too many of the same numeral\n");
	else if (err == 3)
		dprintf(2, "Error: Numerals must be ordered in MDCLXVI order\n");
	else if (err == 4)
		dprintf(2, "Error: Subtraction with DLV is not allowed\n");
	else if (err == 5)
		dprintf(2, "Error: Subtraction with too small value\n");
	else if (err == 6)
		dprintf(2, "Error: Invalid additions after last subtraction\n");
	else if (err == 7)
		dprintf(2, "Error: Subtraction in wrong place\n");
	else if (err == 8)
		dprintf(2, "Error: Addition with subtracting numeral\n");
	exit(1);
}

/*
** Validates format further
** 1. There must not be duplicate of same subtraction.
** 2. After subtraction there may not be addition with subtracting value.
** 3. After last subtractions IX/IV there may not be any further numerals.
*/

void	validate_format_dups(int *numbers, int len)
{
	int i;
	int sub;
	int val;

	i = 0;
	sub = 0;
	val = 0;
	while (i < len)
	{
		if (sub && val)
		{
			if (val == 5 || val == 10)
				print_error(6);
			else if (val == numbers[i])
				print_error(7);
			else if (sub == numbers[i])
				print_error(8);
		}
		if (((i + 1) < len) && (numbers[i + 1] > numbers[i]))
		{
			sub = numbers[i];
			val = numbers[i + 1];
		}
		if (sub && val)
			i += 2;
		else
			i += 1;	
	}
}

/*
** Validates order of roman numerals:
** 1. Numerals must be in order from largest to smallest "MDCLXVI" (except subtracting value).
** 2. DLV (500, 50, 5) may not be used for subtraction.
** 3. Too small value can't be used for subtraction.
*/

void	validate_format_order(int *numbers, int len)
{
	int i;
	int cur_max;

	i = 0;
	if (len > 1 && (numbers[1] > numbers[0]))
		cur_max = numbers[1];
	else
		cur_max = numbers[0];
	while (i < len)
	{
		if (numbers[i] > cur_max)
			print_error(3);
		if ((i + 1) < len)
		{
			if ((numbers[i] == 500 || numbers[i] == 50 || numbers[i] == 5) && (numbers[i + 1] > numbers[i]))
				print_error(4);
			if ((numbers[i + 1] > numbers[i]) && (numbers[i + 1] <= cur_max))
			{
				if ((numbers[i] * 10) < numbers[i + 1])
					print_error(5);
				cur_max = numbers[i + 1];
			}
			else
				cur_max = numbers[i];
		}
		i += 1;
	}
}

/*
** Validates amount of numerals is correct:
** 1. There can't be more than 3 of the same number in row.
** 2. There can't be more than 1 of DLV (500, 50, 5) in row.
*/

void	validate_format_amount(int *numbers, int len)
{
	int i;
	int count;
	int cur_num;

	i = 0;
	count = 1;
	cur_num = 0;
	while (i < len)
	{
		if (cur_num == numbers[i])
		{
			count += 1;
			if (count > 3)
				print_error(2);
			else if ((cur_num == 500 || cur_num == 50 || cur_num == 5) && count > 1)
				print_error(2);
		}
		else
		{
			cur_num = numbers[i];
			count = 1;
		}
		i += 1;
	}
}

/*
** Validates romans
** Check the chars given match our mask "MDCLXVI".
** Also creates, allocates and assigns matching arabic
** values to int array numbers.
*/

int		*validate_chars(char *romans, int len)
{
	int i;
	char *c;
	int values[7] = {1000, 500, 100, 50, 10, 5, 1};
	char mask[] = "MDCLXVI";
	int *numbers;

	i = 0;
	if (!(numbers = (int*)malloc(sizeof(int) * len)))
		print_error(0);
	while(romans[i])
	{
		if (!(c = strchr(mask, romans[i])))
			print_error(1);
		numbers[i] = values[(int)(c - mask)];
		i += 1;
	}
	return(numbers);
}

/*
** Calculates roman numerical value.
** Check if there exists larger value after current one, if there is, we know this
** is subtraction and we add the value to neg, otherwise it is addition and value
** is added to pos. Final value is simply all the positives minus all the negatives.
*/

void	calc_romans(int *numbers, int len)
{
	int i;
	int pos;
	int neg;

	i = 0;
	pos = 0;
	neg = 0;
	while(i < len)
	{
		if ((i + 1) < len)
		{
			if (numbers[i + 1] > numbers[i])
				neg += numbers[i];
			else
				pos += numbers[i];
		}
		else
			pos += numbers[i];
		i += 1;
	}
	printf("%d\n", pos - neg);
}

/*
** Roman numerals to arabic numbers main
** Validating correctness of roman math input was much more difficult than the math.
*/

int		main(int argc, char **argv)
{
	int *numbers;
	int len;

	if (argc != 2)
		print_usage();
	len = strlen(argv[1]);
	numbers = validate_chars(argv[1], len);
	validate_format_amount(numbers, len);
	validate_format_order(numbers, len);
	validate_format_dups(numbers, len);
	calc_romans(numbers, len);
	free(numbers);
	return(0);
}
