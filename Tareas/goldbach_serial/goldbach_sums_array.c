

#include "goldbach_sums_array.h"


int goldbach_sums_array_increase_capacity(goldbach_sums_array_t* array);
void print_sum(goldbach_sums_array_t* array, int64_t amount_addends);

/**
 * @brief initialize the goldbach_sums_array struct
 * @details initialize the goldbach_sums_array struct
 * @param array pointer to the array to be initialized
 * @return returns an integer to check errors
 */
int goldbach_sums_array_init(goldbach_sums_array_t* array, int64_t number,
  bool is_negative_number) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->elements = NULL;
  array->number = number;
  array->is_negative_number = is_negative_number;
  return EXIT_SUCCESS;
}
/**
 * @brief destroys the goldbach_sums_array struct
 * @details initialize the goldbach_sums_array struct
 * @param array pointer to the array to be destroyed
 * @return returns an integer to check errors
 */
void goldbach_sums_array_destroy(goldbach_sums_array_t* array) {
  assert(array);
  array->capacity = 0;
  array->count = 0;
  array->number = 0;
  array->is_negative_number = false;
  free(array->elements);
}

/**
 * @brief appends an element to the goldbach_sums_array struct
 * @details appends an element to the goldbach_sums_array struct
 * @param array pointer to the array
 * @param element element to be Appended
 * @return returns an integer to check errors
 */
int goldbach_sums_array_append(goldbach_sums_array_t* array, int64_t element) {
  assert(array);
  if (array->count == array->capacity) {
    if (goldbach_sums_array_increase_capacity(array) != EXIT_SUCCESS) {
      return EXIT_FAILURE;
    }
  }
  array->elements[array->count++] = element;
  return EXIT_SUCCESS;
}
/**
 * @brief increases the capacity of the goldbach_sums_array struct
 * @details increases the capacity of the goldbach_sums_array struct by making it
 * 10 times bigger
 * @param array pointer to the array
 * @return returns an integer to check errors
 */
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

/**
 * @brief returns the count of elements in the array
 * @details returns the count of elements in the array
 * @param array pointer to the array
 * @return returns the count of elements in the array
 */
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
  if (!array->is_negative_number) {
    printf("%"SCNd64 "%s" "%"SCNd64 "%s", array->number, ": " ,
    get_amount_sums(array), " sums");
  
  } else {
    printf("%s" "%"SCNd64 "%s" "%"SCNd64 "%s", "-", array->number,
     ": " , get_amount_sums(array), " sums: ");
    
    if (array->number % 2 == 0) {
      for (int index = 0; index < array->count; index += 2){ 
        print_sum(array, 2);
        if (index + 2 < array->count) {
          printf(", ");
        }
      }
    } else {
      for (int index = 0; index < array->count; index += 3){
        print_sum(array, 3);
        if (index + 3 < array->count) {
          printf(", ");
        }
      }
    }
  }
}

void print_sum(goldbach_sums_array_t* array, int64_t amount_addends) {
  for (int index = 0; index < amount_addends; index++) {
    printf("%"SCNd64, array->elements[index]);
    if (index + 1 <= amount_addends) {
      printf("%s", " + ");
    }
  }
}