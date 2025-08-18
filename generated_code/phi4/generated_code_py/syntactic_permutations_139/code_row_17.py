import os
import psycopg2

def is_user_moderator(username):
    # Retrieve database connection info from environment variables
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    # Establish the database connection
    conn = psycopg2.connect(
        host=db_host,
        dbname=db_name,
        user=db_user,
        password=db_password
    )
    
    try:
        with conn.cursor() as cur:
            # Execute query to check if the user is a moderator
            cur.execute("SELECT 1 FROM users WHERE username=%s AND is_moderator=True", (username,))
            
            # Fetch one result
            result = cur.fetchone()
            
            # Return True if the user is a moderator, otherwise False
            return bool(result)
    finally:
        conn.close()

# Example usage: Replace 'your_username' with the actual username you want to check.
# print(is_user_moderator('your_username'))