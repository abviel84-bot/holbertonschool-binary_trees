#include "binary_trees.h"

/**
 * tree_height - Measures the height of a tree, using int to avoid
 * unsigned underflow issues
 * @tree: Pointer to the root node of the tree
 *
 * Return: Height of the tree, or -1 if tree is NULL
 */
static int tree_height(const binary_tree_t *tree)
{
	int left_height, right_height;

	if (tree == NULL)
		return (-1);

	left_height = tree_height(tree->left);
	right_height = tree_height(tree->right);

	if (left_height > right_height)
		return (1 + left_height);

	return (1 + right_height);
}

/**
 * binary_tree_balance - Measures the balance factor of a binary tree
 * @tree: Pointer to the root node of the tree to measure the
 * balance factor
 *
 * Return: Balance factor of the tree, or 0 if tree is NULL
 */
int binary_tree_balance(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	return (tree_height(tree->left) - tree_height(tree->right));
}
