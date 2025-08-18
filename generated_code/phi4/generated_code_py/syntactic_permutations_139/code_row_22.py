import os
import psycopg2

def check_user_exists(username):
    try:
        # Fetching database connection details from environment variables
        db_name = os.getenv('DB_NAME')
        db_user = os.getenv('DB_USER')
        db_password = os.getenv('DB_PASSWORD')
        db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not specified
        db_port = os.getenv('DB_PORT', '5432')      # Default to port 5432 if not specified

        # Establishing connection to the database
        conn = psycopg2.connect(
            dbname=db_name,
            user=db_user,
            password=db_password,
            host=db_host,
            port=db_port
        )

        # Creating a cursor object using the cursor() method
        cur = conn.cursor()

        # SQL query to check if the user exists in the users table
        query = "SELECT 1 FROM users WHERE username = %s LIMIT 1;"

        # Executing the SQL command
        cur.execute(query, (username,))

        # Fetching one record from the query result
        result = cur.fetchone()

        # Closing the cursor and connection to the database
        cur.close()
        conn.close()

        # Return True if user exists, otherwise False
        return bool(result)
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

# Example usage:
# result = check_user_exists('some_username')
# print(result)  # Output will be either True or False based on the existence of 'some_username'