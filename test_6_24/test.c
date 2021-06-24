#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int BubbleSort(int s[], int n, int k)
{
	int i, j, tmp;
	for (i = n; i > 1; i--)
	{
		for (j = 0; j < i - 1; j++)
		{
			if (s[j] < s[j + 1])
			{
				tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
		}
	}
	return s[k - 1];
}

void mysort(int s[], int n)
{
	int i, j, tmp;
	for (i = n; i > 1; i--)
	{
		for (j = 0; j < i - 1; j++)
		{
			if (s[j] < s[j + 1])
			{
				tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
		}
	}
}

int Bubble_Sort(int s[], int n, int k)
{
	int i, j, * p, tmp;
	if (k <= 0)
		return -1;
	p = (int*)malloc(k * sizeof(int));
	if (!p)
		return -1;
	for (i = 0; i < k; i++)
	{
			p[i] = s[i];
	}
	mysort(p, k);
	for (i = k; i < n; i++)
	{
		tmp = s[i];
		for (j = k-1; j > 0 && tmp > p[j]; j--)
		{
			p[j] = p[j - 1];
		}
		p[j] = tmp;
	}
	tmp = p[k - 1];
	free(p);
	return tmp;
}

void riddle(char (*p1)[4], int row, int col, char** p2, int sz)
{
	int i, j, k, t, m, n;
	for (k = 0; k < sz; k++)
	{
		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				int len = strlen(p2[k]);
				if (i + len - 1 < row)
				{
					for (m = i, t = 0; t < len && p1[m][j] == p2[k][t]; t++, m++)
						;
					if (t == len)
						printf("单词 %s从(%d,%d)到(%d,%d);\n", p2[k], i + 1, j + 1, i + len, j + 1);
					for (m = i, t = len-1; t >= 0 && p1[m][j] == p2[k][t]; t--, m++)
						;
					if (t == -1)
						printf("单词 %s从(%d,%d)到(%d,%d);\n", p2[k], i + len, j + 1, i + 1, j + 1);
				}

				if (j + len - 1 < col)
				{
					for (m = j, t = 0; t < len && p1[i][m] == p2[k][t]; t++, m++)
						;
					if (t == len)
						printf("单词 %s从(%d,%d)到(%d,%d);\n", p2[k], i + 1, j + 1, i + 1, j + len);
					for (m = j, t = len - 1; t >= 0 && p1[i][m] == p2[k][t]; t--, m++)
						;
					if (t == -1)
						printf("单词 %s从(%d,%d)到(%d,%d);\n", p2[k], i + 1, j + len, i + 1, j + 1);
				}

				if (j + len - 1 < col && i+ len - 1 < row)
				{
					for (m = i, n = j, t = 0; t < len && p1[m][n] == p2[k][t]; t++, m++, n++)
						;
					if (t == len)
						printf("单词 %s从(%d,%d)到(%d,%d);\n", p2[k], i + 1, j + 1, i + len, j + len);
					for (m = i, n = j, t = len - 1; t >= 0 && p1[m][n] == p2[k][t]; t--, m++, n++)
						;
					if (t == -1)
						printf("单词 %s从(%d,%d)到(%d,%d);\n", p2[k], i + len, j + len, i + 1, j + 1);
				}

				if (j + len - 1 < col && i - len + 1 >= 0)
				{
					for (m = i, n = j, t = 0; t < len && p1[m][n] == p2[k][t]; t++, m--, n++)
						;
					if (t == len)
						printf("单词 %s从(%d,%d)到(%d,%d);\n", p2[k], i + 1, j + 1, i - len + 2, j + len);
					for (m = i, n = j, t = len - 1; t >= 0 && p1[m][n] == p2[k][t]; t--, m--, n++)
						;
					if (t == -1)
						printf("单词 %s从(%d,%d)到(%d,%d);\n", p2[k], i - len + 2, j + len, i + 1, j + 1);
				}
			}
		}
	}
}

int main()
{
	/*int arr[] = { 1,2,3,4,100 };
	int ret = BubbleSort(arr, 5, 5);
	int ret = Bubble_Sort(arr, 5, 3);
	printf("%d\n", ret);*/


	char arr[4][4] = { {'t','h','i','s'},{'w','a','t','s'},{'o','a','h','g'},{'f','g','d','t'}};
	char* arr2[] = { "this","two","fat","that" };

	riddle(arr, 4, 4, arr2, 4);

	return 0;
}