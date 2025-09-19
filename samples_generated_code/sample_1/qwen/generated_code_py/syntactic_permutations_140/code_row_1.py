import sqlite3

# Connect to the SQLite database (or create it if it doesn't exist)
connection = sqlite3.connect('example.db')

# Create a cursor object using the connection
cursor = connection.cursor()

# Define the SQL query you want to execute
query = "SELECT * FROM your_table_name;"

try:
    # Execute the query
    cursor.execute(query)
    
    # Fetch all results from the executed query
    results = cursor.fetchall()
    
    # Print the results
    for row in results:
        print(row)

except sqlite3.Error as e:
    print(f"An error occurred: {e}")

finally:
    # Close the cursor and connection to clean up
    cursor.close()
    connection.close()