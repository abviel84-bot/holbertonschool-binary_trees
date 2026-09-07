#include "binary_trees.h"

/**
 * tree_height - Measures the height of a tree
 * @tree: Pointer to the root node of the tree
 *
 * Return: Height of the tree, or 0 if tree is NULL
 */
static size_t tree_height(const binary_tree_t *tree)
{
	size_t left_height, right_height;

	if (tree == NULL)
		return (0);

	if (tree->left == NULL && tree->right == NULL)
		return (0);

	left_height = tree_height(tree->left);
	right_height = tree_height(tree->right);

	if (left_height > right_height)
		return (1 + left_height);

	return (1 + right_height);
}

/**
 * tree_size - Measures the size of a tree
 * @tree: Pointer to the root node of the tree
 *
 * Return: Size of the tree, or 0 if tree is NULL
 */
static size_t tree_size(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	return (1 + tree_size(tree->left) + tree_size(tree->right));
}

/**
 * binary_tree_is_perfect - Checks if a binary tree is perfect
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if the tree is perfect, 0 otherwise or if tree is NULL
 */
int binary_tree_is_perfect(const binary_tree_t *tree)
{
	size_t height, size, expected_size, i;

	if (tree == NULL)
		return (0);

	height = tree_height(tree);
	size = tree_size(tree);

	expected_size = 1;
	for (i = 0; i < height; i++)
		expected_size = expected_size * 2 + 1;

	return (size == expected_size);
}
