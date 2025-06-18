int main(void) {
  // Initialize WSGI server
  PyObject *app = make_wsgi_app();
  int status;
  
  // Initialize MySQL database connection
  db = mysql_init(NULL);
  if (!db) {
    fprintf(stderr, "Failed to initalize database\n");
    return EXIT_FAILURE;
  }

  // Setup the database connection information
  status = mysql_real_connect(db, HOSTNAME, USERNAME, PASSWORD, DATABASE_NAME);
  if (status) {
    fprintf(stderr, "Failed to connect to database\n");
    return EXIT_FAILURE;
  }

  // Execute the query and print the results
  PyObject *results = mysql_query(db, "SELECT max(temperature) FROM weather WHERE latitude=%s AND longitude=%s AND year=%d AND month=%d", latitude, longitude, year, month);
  printf("Maximum temperature: %f\n", results);
  
  // Cleanup
  mysql_free_result(results);
  mysql_close(db);
  Py_DECREF(app);
  return EXIT_SUCCESS;
}