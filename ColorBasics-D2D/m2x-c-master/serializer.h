#ifndef M2X_SERIALIZER_H
#define M2X_SERIALIZER_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct json_context {
  char* buf;
  int index;
  int length;
} json_context;

/* Creating a json_context and start building an array/object */
json_context *json_start_array();
json_context *json_start_object();

/* Functions used to pack nested arrays/objects. Notice that it is
 * your own responsibility to ensure that these functions are called
 * in matched pairs. The serializer itself does not check for matching
 * calls.
 * Notice the array/object here can also be used as items in an
 * outer-level array, or a value in an object. In other works,
 * array/object can work in a nested way.
 */
json_context *json_pack_array_start(json_context *json);
json_context *json_pack_array_end(json_context *json);
json_context *json_pack_object_start(json_context *json);
json_context *json_pack_object_end(json_context *json);

/* This function is used to pack a key in JSON objects, it must
 * be followed by one of the following functions, or one of
 * +json_pack_array_start+ and +json_pack_object_start+ to specify
 * the value for this key in the object.
 */
json_context *json_pack_key(json_context *json, const char *key);

/* The following functions are used to specify primitive typed
 * values. They can either be the item of an array, of a value in
 * a key/value pair belonging to a JSON object.
 */
json_context *json_pack_null(json_context *json);
json_context *json_pack_boolean(json_context *json, int b);
json_context *json_pack_fixnum(json_context *json, int n);
json_context *json_pack_string(json_context *json, const char *str);
json_context *json_pack_value(json_context *json, const char *value);

/* Ends the most-outer level array/object, frees json_context object,
 * and returns the generated JSON string. The caller is responsible
 * for freeing the char buffer.
 */
char *json_end_array(json_context *json);
char *json_end_object(json_context *json);

#if defined(__cplusplus)
}  /* extern "C" { */
#endif

#endif  /* M2X_SERIALIZER_H */

