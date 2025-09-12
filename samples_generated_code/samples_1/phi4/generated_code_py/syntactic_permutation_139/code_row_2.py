import os
import psycopg2

def is_user_moderator(username):
    try:
        # Retrieve database credentials from environment variables
        db_name = os.getenv('DB_NAME')
        db_user = os.getenv('DB_USER')
        db_password = os.getenv('DB_PASSWORD')
        db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not specified
        db_port = os.getenv('DB_PORT', '5432')       # Default to port 5432 if not specified

        # Connect to the database
        conn = psycopg2.connect(
            dbname=db_name,
            user=db_user,
            password=db_password,
            host=db_host,
            port=db_port
        )
        
        cur = conn.cursor()
        
        # Execute query to check if the user is a moderator
        cur.execute("SELECT role FROM users WHERE username = %s", (username,))
        result = cur.fetchone()

        if result and result[0] == 'moderator':
            return True
        
        return False

    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        # Close the cursor and connection
        if conn:
            cur.close()
            conn.close()

# Example usage:
# is_moderator = is_user_moderator('example_username')
# print(is_moderator)