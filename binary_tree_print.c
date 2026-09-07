#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_trees.h"

void binary_tree_print(const binary_tree_t *tree);

/**
 * struct pos_s - Position of a node for printing
 * @n: Value of the node
 * @row: Row in which to print
 * @col: Column in which to print
 */
typedef struct pos_s
{
	int n;
	int row;
	int col;
} pos_t;

/**
 * height - Measures the height of a binary tree
 * @tree: Tree to measure
 *
 * Return: Height, or 0 if tree is NULL
 */
static int height(const binary_tree_t *tree)
{
	int left, right;

	if (tree == NULL)
		return (0);

	left = height(tree->left);
	right = height(tree->right);

	return (1 + (left > right ? left : right));
}

/**
 * fill_positions - Fills an array with node positions
 * @tree: Current node
 * @depth: Current depth
 * @left: Left bound of the column range
 * @right: Right bound of the column range
 * @positions: Array to fill
 * @count: Pointer to current count of positions
 */
static void fill_positions(const binary_tree_t *tree, int depth,
	int left, int right, pos_t *positions, int *count)
{
	int mid;

	if (tree == NULL)
		return;

	mid = (left + right) / 2;
	positions[*count].n = tree->n;
	positions[*count].row = depth;
	positions[*count].col = mid;
	(*count)++;

	fill_positions(tree->left, depth + 1, left, mid - 1, positions, count);
	fill_positions(tree->right, depth + 1, mid + 1, right, positions, count);
}

/**
 * count_nodes - Counts the number of nodes in a tree
 * @tree: Tree to count
 *
 * Return: Number of nodes
 */
static int count_nodes(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (1 + count_nodes(tree->left) + count_nodes(tree->right));
}

/**
 * binary_tree_print - Prints a binary tree
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	int h, width, node_count, i, r, c;
	pos_t *positions;
	char **grid;

	if (tree == NULL)
		return;

	h = height(tree);
	width = 1;
	for (i = 0; i < h; i++)
		width *= 2;
	width = width * 6;

	node_count = count_nodes(tree);
	positions = malloc(sizeof(pos_t) * node_count);
	if (positions == NULL)
		return;

	i = 0;
	fill_positions(tree, 0, 0, width - 1, positions, &i);

	grid = malloc(sizeof(char *) * h);
	for (r = 0; r < h; r++)
	{
		grid[r] = malloc(sizeof(char) * (width + 1));
		memset(grid[r], ' ', width);
		grid[r][width] = '\0';
	}

	for (i = 0; i < node_count; i++)
	{
		char buf[16];
		int len, start;

		sprintf(buf, "(%03d)", positions[i].n);
		len = strlen(buf);
		start = positions[i].col - len / 2;
		if (start < 0)
			start = 0;
		for (c = 0; c < len && start + c < width; c++)
			grid[positions[i].row][start + c] = buf[c];
	}

	for (r = 0; r < h; r++)
	{
		printf("%s\n", grid[r]);
		free(grid[r]);
	}
	free(grid);
	free(positions);
}
