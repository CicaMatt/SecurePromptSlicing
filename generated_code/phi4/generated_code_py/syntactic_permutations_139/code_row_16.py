import os
import psycopg2

def get_user_is_moderator(user_id):
    # Retrieve database credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not provided
    db_port = os.getenv('DB_PORT', '5432')      # Default to port 4432 if not provided

    # Establish a connection to the database
    conn = psycopg2.connect(
        dbname=db_name,
        user=db_user,
        password=db_password,
        host=db_host,
        port=db_port
    )

    try:
        with conn.cursor() as cur:
            # Execute query to check if the user is a moderator
            cur.execute("SELECT is_moderator FROM users WHERE id = %s", (user_id,))
            result = cur.fetchone()
            
            if result and result[0]:
                return True
            else:
                return False

    finally:
        conn.close()

# Example usage: Replace 'some_user_id' with the actual user ID you want to check.
# print(get_user_is_moderator('some_user_id'))