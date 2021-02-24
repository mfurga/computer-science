#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "binary_search_tree.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

binary_tree_node_t *create_binary_tree(int value)
{
  binary_tree_node_t *root = (binary_tree_node_t *)malloc(sizeof(binary_tree_node_t));
  if (root == NULL) {
    exit(EXIT_FAILURE);
  }
  root->value = value;
  root->parent = NULL;
  root->left = NULL;
  root->right = NULL;
  return root;
}

static binary_tree_node_t *add_left_child(binary_tree_node_t *node, int value)
{
  node->left = (binary_tree_node_t *)malloc(sizeof(binary_tree_node_t));
  if (node->left == NULL) {
    return NULL;
  }
  node->left->value = value;
  node->left->parent = node;
  node->left->left = NULL;
  node->left->right = NULL;
  return node->left;
}

static binary_tree_node_t *add_right_child(binary_tree_node_t *node, int value)
{
  node->right = (binary_tree_node_t *)malloc(sizeof(binary_tree_node_t));
  if (node->right == NULL) {
    return NULL;
  }
  node->right->value = value;
  node->right->parent = node;
  node->right->left = NULL;
  node->right->right = NULL;
  return node->right;
}

void insert(binary_tree_node_t *node, int value)
{
  binary_tree_node_t *curr = node;

  while (curr->value > value && curr->left != NULL ||
         curr->value < value && curr->right != NULL) {
    if (curr->value > value)
      curr = curr->left;
    else
      curr = curr->right;
  }

  if (curr->value > value)
    add_left_child(curr, value);
  else if (curr->value < value)
    add_right_child(curr, value);
  else return;  /* If they're the same, do nothing */
}

binary_tree_node_t *find(binary_tree_node_t *node, int value)
{
  while (node != NULL) {
    if (node->value == value)
      return node;

    if (node->value > value)
      node = node->left;
    else if (node->value < value)
      node = node->right;
  }
  return NULL;
}

void delete(binary_tree_node_t *node, int value)
{
  binary_tree_node_t *curr = find(node, value);
  if (curr == NULL)
    return;

  /* The node doesn't have any children. */
  if (curr->left == NULL && curr->right == NULL) {
    if (curr->parent->left == curr)
      curr->parent->left = NULL;
    else
      curr->parent->right = NULL;

    free(curr);
    return;
  }

  /* The node has only a left children. */
  if (curr->right == NULL) {
    curr->left->parent = curr->parent;

    if (curr->parent->left == curr)
      curr->parent->left = curr->left;
    else
      curr->parent->right = curr->left;

    free(curr);
    return;
  }

  /* The node has only a right children. */
  if (curr->left == NULL) {
    curr->right->parent = curr->parent;

    if (curr->parent->left == curr)
      curr->parent->left = curr->right;
    else
      curr->parent->right = curr->right;

    free(curr);
    return;
  }

  /* The node has two children. */
  /* Now we're looking for the smallest value in the right subtree. */
  binary_tree_node_t *smallest = curr->right;

  while (smallest->left != NULL) {
    smallest = smallest->left;
  }

  curr->value = smallest->value;
  return delete(smallest, smallest->value);
}

int height(binary_tree_node_t *node)
{
  if (node == NULL)
    return -1;
  return 1 + max(height(node->left), height(node->right));
}

int min_height(binary_tree_node_t *node)
{
  if (node == NULL)
    return -1;
  return 1 + min(min_height(node->left), min_height(node->right));
}

int nodes_with_one_child(binary_tree_node_t *node)
{
  if (node == NULL)
    return 0;
  if (node->left == NULL ^ node->right == NULL)
    return 1;
  return nodes_with_one_child(node->left) +
         nodes_with_one_child(node->right);
}

binary_tree_node_t *maximum(binary_tree_node_t *node)
{
  if (node == NULL)
    return NULL;

  while (node->right != NULL)
    node = node->right;
  return node;
}

binary_tree_node_t *minimum(binary_tree_node_t *node)
{
  if (node == NULL)
    return NULL;

  while (node->left != NULL)
    node = node->left;
  return node;
}

int count(binary_tree_node_t *node)
{
  if (node == NULL)
    return 0;
  return 1 + count(node->left) + count(node->right);
}

int leaf(binary_tree_node_t *node)
{
  if (node == NULL)
    return 0;
  if (node->left == NULL && node->left == NULL)
    return 1;
  return leaf(node->left) + leaf(node->right);
}

bool is_between(binary_tree_node_t *node, int min, int max)
{
  if (node == NULL)
    return true;

  return (node->value > min && node->value < max &&
          is_between(node->left, min, node->value) &&
          is_between(node->right, node->value, max));
}

/* 
  We can also use the in-order traversal and check each time
  that incoming data is sorted or not.
 */
bool is_binary_search_tree(binary_tree_node_t *root)
{
  return is_between(root, INT_MIN, INT_MAX);
}

binary_tree_node_t *successor(binary_tree_node_t *root, int value)
{
  binary_tree_node_t *node = find(root, value);
  if (node == NULL)
    return NULL;

  /* The node has a right subtree. */
  if (node->right != NULL)
    return minimum(node->right);

  /* The node doesn't have a right subtree. */
  binary_tree_node_t *parent = node->parent;
  while (parent != NULL && node == parent->right) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}

binary_tree_node_t *predecessor(binary_tree_node_t *root, int value)
{
  binary_tree_node_t *node = find(root, value);
  if (node == NULL)
    return NULL;

  /* The node has a left subtree. */
  if (node->left != NULL)
    return maximum(node->left);

  /* The node doesn't have a left subtree. */
  binary_tree_node_t *parent = node->parent;
  while (parent != NULL && node == node->left) {
    node = parent;
    parent = parent->parent;
  }
  return parent;
}
