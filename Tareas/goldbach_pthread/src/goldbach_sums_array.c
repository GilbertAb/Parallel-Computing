// Copyright 2021 Gilbert Marquez Aldana <gilbert.marquez@ucr.ac.cr>

#include "goldbach_sums_array.h"

/**
 * @brief returns the amount of sums in the array.
 * @details returns the amount of sums in the array.
 * @param array pointer to the array.
 * @return the amount of sums in the array.
 */
int64_t get_amount_sums(goldbach_sums_array_t* array);

/**
 * @brief increases the capacity of the goldbach_sums_array struct.
 * @details increases the capacity of the goldbach_sums_array struct by making it
 * 10 times bigger.
 * @param array pointer to the array.
 * @return returns an integer to check errors.
 */
int goldbach_sums_array_increase_capacity(goldbach_sums_array_t* array);

/**
 * @brief prints one sum of the number.
 * @details checks if the addends should be 2 or 3, then prints one 
 * sum of the number.
 * @param array pointer to the array.
 * @param index_array index of the array were the sum starts.
 * @param amount_addends amount of addends that the sum has.
 */
void print_sum(goldbach_sums_array_t* array, int64_t index_array,
  int64_t amount_addends);

int goldbach_sums_array_init(goldbach_sums_array_t* array, int64_t number) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  array->number = number;
  array->is_negative_number = false;
  
  if (number < 0) {
    array->number = number * (-1);
    array->is_negative_number = true;
  }

  return EXIT_SUCCESS;
}

void goldbach_sums_array_destroy(goldbach_sums_array_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->number = 0;
  array->is_negative_number = false;
  free(array->elements);
}

int goldbach_sums_array_append(goldbach_sums_array_t* array, int64_t element) {
  assert(array);
  if (element < 0) {
    element *= -1;
    array->is_negative_number = true;
  }
  if (array->count == array->capacity) {
    if (goldbach_sums_array_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}

int goldbach_sums_array_increase_capacity(goldbach_sums_array_t* array) {
  int64_t new_capacity = 10 * (array->capacity ? array->capacity : 1);
  int64_t* new_elements = (int64_t*)
    realloc(array->elements, new_capacity * sizeof(int64_t));

  if (new_elements) {
    array->capacity = new_capacity;
    array->elements = new_elements;
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

int64_t get_amount_sums(goldbach_sums_array_t* array) {
  int64_t amount_sums = 0;

  if (array->number % 2 == 0) {
    amount_sums = array->count / 2;
  } else {
    amount_sums = array->count / 3;
  }
  return amount_sums;
}

void goldbach_sums_array_print(goldbach_sums_array_t* array) {
  if (array->number < 0 || array->number > 5) {
    if (!array->is_negative_number) {
      printf("%"SCNd64 "%s" "%"SCNd64 "%s", array->number, ": " ,
      get_amount_sums(array), " sums");

    } else {
      printf("%s" "%"SCNd64 "%s" "%"SCNd64 "%s", "-", array->number,
        ": " , get_amount_sums(array), " sums: ");

      if (array->number % 2 == 0) {
        for (int index = 0; index < array->count; index += 2) {
          print_sum(array, index, 2);
          if (index + 2 < array->count) {
            printf(", ");
          }
        }
      } else {
        for (int index = 0; index < array->count; index += 3) {
          print_sum(array, index, 3);
          if (index + 3 < array->count) {
            printf(", ");
          }
        }
      }
    }
  } else {
    if (array->is_negative_number) {
      printf("%"SCNd64 "%s", -array->number, ": NA");
    } else {
      printf("%"SCNd64 "%s", array->number, ": NA");
    }
  }
  printf("%s", "\n");
}

void print_sum(goldbach_sums_array_t* array, int64_t index_array,
  int64_t amount_addends) {
  for (int64_t index = 0; index < amount_addends; index++) {
    printf("%"SCNd64, array->elements[index_array++]);
    if (index + 1 < amount_addends) {
      printf("%s", " + ");
    }
  }
}
