#include <stdio.h>
#include "global.h"
#include "pool/pool.h"
#include "list/list.h"
#include "list/linked_list.h"
#include "stack/stack.h"
#include "stack/linked_stack.h"
#include "queue/queue.h"
#include "tree/binary_tree.h"
#include "tree/tree.h"

void print_data_int(_p_adt p_ad);

void print_data_int_array(_p_adt p_ad, unsigned size);

void pool_test() {

    unsigned n = 3;
    _p_adt p_ad_array = get_ad_objects(n, sizeof(int));

    for (int i = 0; i < n; ++i) {

        *(int *) p_ad_array[i].data = i * 2;
    }

    print_data_int_array(p_ad_array, n);

    free_data(p_ad_array);
}

static void list_test() {

    unsigned size = 4;
    _p_list p_list = list_init(16);

    _p_adt p_ad = get_ad_objects(size, sizeof(int));

    for (int j = 0; j < size; ++j) {

        *(int *) p_ad[j].data = j;
    }

    for (int i = 0; i < 3; ++i) {

        list_append(p_list, p_ad + i);
    }

    list_insert(p_list, 1, p_ad + 3);

    list_remove_at(p_list, 2);
    list_remove_at(p_list, 1);

    int index = list_find(p_list, p_ad + 2);

    printf("%d\n", index);

    list_print(p_list, print_data_int);

    list_clear(p_list);
}

static void linked_list_test() {

    unsigned size = 4;

    _p_linked_list p_linked_list = linked_list_init();
    _p_adt p_ad = get_ad_objects(size, sizeof(int));

    int *p_int_array = alloc_memory(sizeof(int) * size);

    for (int j = 0; j < size; ++j) {

        p_ad[j].data = p_int_array + j;
        *(p_int_array + j) = j * 2;
    }

    for (int i = 0; i < 1; ++i) {

        linked_list_insert_first_after(p_linked_list, p_ad + i);
    }

    linked_list_insert_last_before(p_linked_list, p_ad + 2);
    linked_list_insert_first_before(p_linked_list, p_ad + 1);
    linked_list_insert_last_after(p_linked_list, p_ad + 3);

    _p_adt p_ad1 = get_ad_objects(1, sizeof(int));
    int *p_int1 = alloc_memory(sizeof(int));
    *p_int1 = 100;
    p_ad1->data = p_int1;

    linked_list_insert_after(p_linked_list, p_ad + 1, p_ad1);

    linked_list_remove(p_linked_list, p_ad1);

    print_linked_list(p_linked_list, print_data_int);
    return;

}

static void stack_test() {

    _p_stack p_stack = stack_init(NULL, NULL);

    unsigned size = 4;
    _p_adt p_ad = get_ad_objects(size, sizeof(int));
    int *p_int_array = alloc_memory(sizeof(int) * size);

    for (int j = 0; j < size; ++j) {

        p_ad[j].data = p_int_array + j;
        *(p_int_array + j) = j * 2;
    }

    stack_push(p_stack, p_ad);
    _p_adt p_ad1 = stack_pop(p_stack);
    print_data_int(p_ad1);
    stack_push(p_stack, p_ad + 1);
    stack_push(p_stack, p_ad + 2);
    stack_push(p_stack, p_ad + 3);
    p_ad1 = stack_pop(p_stack);
    print_data_int(p_ad1);
    p_ad1 = stack_pop(p_stack);
    print_data_int(p_ad1);
    p_ad1 = stack_pop(p_stack);
    print_data_int(p_ad1);

    return;
}

static void linked_stack_test() {

    _p_stack p_stack = linked_stack_init(NULL, NULL);

    unsigned size = 4;
    _p_adt p_ad = get_ad_objects(size, sizeof(int));

    for (int j = 0; j < size; ++j) {

        *(int *) p_ad[j].data = j * 2;
    }

    linked_stack_push(p_stack, p_ad);
    _p_adt p_ad1 = linked_stack_pop(p_stack);
    print_data_int(p_ad1);
    linked_stack_push(p_stack, p_ad + 1);
    linked_stack_push(p_stack, p_ad + 2);
    linked_stack_push(p_stack, p_ad + 3);
    p_ad1 = linked_stack_pop(p_stack);
    print_data_int(p_ad1);
    p_ad1 = linked_stack_pop(p_stack);
    print_data_int(p_ad1);
    p_ad1 = linked_stack_pop(p_stack);
    print_data_int(p_ad1);

    return;
}

static void queue_test() {

    unsigned size = 4;
    _p_adt p_ad = get_ad_objects(size, sizeof(int));

    for (int j = 0; j < size; ++j) {

        *(int *) p_ad[j].data = j * 2;
    }

    _p_queue p_queue = queue_init(NULL, NULL);

    queue_enqueue(p_queue, p_ad);
    queue_enqueue(p_queue, p_ad + 2);
    queue_enqueue(p_queue, p_ad + 3);

    _p_adt p_ad1 = queue_dequeue(p_queue);
    print_data_int(p_ad1);
    p_ad1 = queue_dequeue(p_queue);
    print_data_int(p_ad1);
    p_ad1 = queue_dequeue(p_queue);
    print_data_int(p_ad1);

    queue_enqueue(p_queue, p_ad + 1);

    p_ad1 = queue_dequeue(p_queue);
    print_data_int(p_ad1);
}


static void binary_tree_test() {

    unsigned size = 8;
    _p_adt p_ad = get_ad_objects(size, sizeof(int));

    for (int j = 0; j < size; ++j) {

        *(int *) p_ad[j].data = j;
    }

    _p_binary_tree p_binary_tree = binary_tree_init(p_ad);

    _p_binary_tree_node root = binary_tree_find_ad(p_binary_tree, p_ad);

    if (root != NULL) {

        _p_binary_tree_node node1 = binary_tree_add_left_child_ad(p_binary_tree, root, p_ad + 1);
        _p_binary_tree_node node2 = binary_tree_add_right_child_ad(p_binary_tree, root, p_ad + 2);

        _p_binary_tree_node node3 = binary_tree_add_left_child_ad(p_binary_tree, node1, p_ad + 3);
        _p_binary_tree_node node4 = binary_tree_add_right_child_ad(p_binary_tree, node1, p_ad + 4);

        _p_binary_tree_node node5 = binary_tree_add_right_child_ad(p_binary_tree, node2, p_ad + 5);
        _p_binary_tree_node node6 = binary_tree_add_right_child_ad(p_binary_tree, node3, p_ad + 6);
        _p_binary_tree_node node7 = binary_tree_add_right_child_ad(p_binary_tree, node4, p_ad + 7);

//        _p_binary_tree_node *order_node_array = pre_order_traverse(root);
//        _p_binary_tree_node *order_node_array = in_order_traverse(root);
        _p_binary_tree_node *order_node_array = post_order_traverse(root);

        unsigned index = 0;
        while (order_node_array[index] != NULL) {

            print_data_int(order_node_array[index]->p_ad);
            ++index;
        }
        printf("\n");
        return;
    }
}

static void tree_test() {

    unsigned size = 6;
    _p_adt p_ad = get_ad_objects(size, sizeof(int));

    for (int i = 0; i < size; ++i) {

        *((int *) (p_ad + i)->data) = i;
    }

    _p_tree p_tree = tree_init(p_ad);

    _p_tree_node ptn1 = tree_make_node(p_tree, p_ad + 1);
    _p_tree_node ptn2 = tree_make_node(p_tree, p_ad + 2);
    _p_tree_node ptn3 = tree_make_node(p_tree, p_ad + 3);
    _p_tree_node ptn4 = tree_make_node(p_tree, p_ad + 4);
    _p_tree_node ptn5 = tree_make_node(p_tree, p_ad + 5);

    tree_add_child_node(p_tree->root, ptn1);
    tree_add_child_node(p_tree->root, ptn3);
    tree_add_child_node(p_tree->root, ptn4);
    tree_add_child_node(ptn1, ptn5);
    tree_add_child_node(ptn1, ptn2);

    _p_list p_list3 = tree_breadth_first_traverse(p_tree);

    for (int k = 0; k < p_list3->size; ++k) {

        print_data_int(((_p_tree_node) p_list3->list[k]->data)->p_ad);
    }

    printf("\n");

    _p_list p_list = tree_depth_first_traverse(p_tree, true);
    for (int j = 0; j < p_list->size; ++j) {

        print_data_int(((_p_tree_node) p_list->list[j]->data)->p_ad);
    }

    printf("\n");
    _p_list p_list1 = tree_depth_first_traverse(p_tree, false);
    for (int j = 0; j < p_list1->size; ++j) {

        print_data_int(((_p_tree_node) p_list1->list[j]->data)->p_ad);
    }
}

unsigned count_test(unsigned x) {

    static unsigned count = 0;

    if (x > 0) {

        count++;
        count_test(--x);
    }

    return count;
}

int main() {

    _p_memory_pool pool = init_pool();

//    pool_test();
//    list_test();
//    linked_list_test();
//    stack_test();
//    queue_test();
    binary_tree_test();

//    tree_test();
    destroy_pool(pool);

//    unsigned count = count_test(262094);//max value 262094 for iteration
//    printf("%d\n", count);
    return 0;
}


void print_data_int(_p_adt p_ad) {

    if (valid_data(p_ad)) {

        printf("%d ", *((int *) p_ad->data));
    }
}

void print_data_int_array(_p_adt p_ad, unsigned size) {

    for (int i = 0; i < size; ++i) {

        print_data_int(p_ad + i);
    }
}
