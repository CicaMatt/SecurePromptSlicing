import os
import psycopg2

def is_user_moderator(user_id):
    # Retrieve database connection details from environment variables
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
        
        cursor = connection.cursor()
        
        # Execute query to check if the user is a moderator
        query = "SELECT 1 FROM users WHERE id = %s AND is_moderator = TRUE"
        cursor.execute(query, (user_id,))
        
        result = cursor.fetchone()

        # Return True if the user is a moderator, False otherwise
        return result is not None
    
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

    finally:
        if 'connection' in locals() and connection:
            connection.close()