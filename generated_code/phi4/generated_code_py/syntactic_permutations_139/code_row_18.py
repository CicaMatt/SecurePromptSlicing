import os
import psycopg2

def is_moderator(user_id):
    # Get database connection details from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not specified
    db_port = os.getenv('DB_PORT', '5432')       # Default to port 5432 if not specified

    try:
        # Connect to the database
        connection = psycopg2.connect(
            dbname=db_name,
            user=db_user,
            password=db_password,
            host=db_host,
            port=db_port
        )

        # Create a cursor object using the connection
        cursor = connection.cursor()

        # Execute the query to check if the user is a moderator
        query = "SELECT role FROM users WHERE user_id = %s"
        cursor.execute(query, (user_id,))
        
        # Fetch the result
        result = cursor.fetchone()
        
        # Check if the fetched role is 'moderator'
        if result and result[0] == 'moderator':
            return True
        
    except Exception as e:
        print(f"An error occurred: {e}")
    
    finally:
        # Close the cursor and connection
        if cursor:
            cursor.close()
        if connection:
            connection.close()

    return False

# Example usage (uncomment to test, ensure environment variables are set)
# user_id = 1
# print(is_moderator(user_id))