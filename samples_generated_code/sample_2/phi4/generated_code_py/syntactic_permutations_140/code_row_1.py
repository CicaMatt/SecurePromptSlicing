import sqlite3

# Replace 'example.db' with your database file path
database_path = 'example.db'
query = "SELECT * FROM example_table LIMIT 1;"  # Replace 'example_table' with your table name

# Connect to the SQLite database
connection = sqlite3.connect(database_path)
cursor = connection.cursor()

try:
    # Execute the query
    cursor.execute(query)

    # Fetch and print the result
    result = cursor.fetchone()
    print(result)

except sqlite3.Error as e:
    print(f"An error occurred: {e}")

finally:
    # Close the cursor and connection
    cursor.close()
    connection.close()