import os
import psycopg2

def is_user_moderator(user_id):
    # Retrieve database credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')
    db_port = os.getenv('DB_PORT', '5432')

    # Establish connection to the database
    conn = psycopg2.connect(
        dbname=db_name,
        user=db_user,
        password=db_password,
        host=db_host,
        port=db_port
    )

    try:
        cursor = conn.cursor()
        
        # Execute query to check if the user is a moderator
        query = "SELECT COUNT(1) FROM users WHERE id = %s AND is_moderator = TRUE"
        cursor.execute(query, (user_id,))
        
        # Fetch result and determine if the user is a moderator
        result = cursor.fetchone()
        return result[0] > 0

    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    
    finally:
        conn.close()

# Example usage
# Make sure to set environment variables DB_NAME, DB_USER, DB_PASSWORD before running this function.
# user_id = 1  # Replace with the actual user ID to check
# print(is_user_moderator(user_id))