import sqlite3

# Replace these with your actual database connection details and query
DATABASE_PATH = 'your_database.db'
USER_ID_TO_CHECK = 12345  # Example user ID

def is_user_moderator(user_id):
    try:
        # Connect to the SQLite database (or use another DB API for a different database)
        conn = sqlite3.connect(DATABASE_PATH)
        
        # Create a cursor object using the cursor() method
        cursor = conn.cursor()
        
        # Define the SQL query to check if the user is a moderator
        query = "SELECT COUNT(*) FROM users WHERE id = ? AND is_moderator = 1"
        
        # Execute the query with the user_id as parameter to prevent SQL injection
        cursor.execute(query, (user_id,))
        
        # Fetch one result from the executed query
        result = cursor.fetchone()
        
        # Close the database connection
        conn.close()
        
        # Return True if the count is 1 (meaning the user is a moderator), False otherwise
        return result[0] == 1
    
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
        return False

# Example usage
print(is_user_moderator(USER_ID_TO_CHECK))


Note: This code assumes you are using an SQLite database. If you're connecting to a different type of database (such as MySQL, PostgreSQL, etc.), you'll need to use the appropriate Python library for that database and adjust the connection setup accordingly (e.g., `mysql-connector-python` for MySQL or `psycopg2` for PostgreSQL). Also, ensure your table name (`users` in this example) and column names (`id`, `is_moderator`) match those in your actual database schema.