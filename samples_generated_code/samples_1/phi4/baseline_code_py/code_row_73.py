import os
import psycopg2

def is_user_moderator(user_id):
    # Get credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')
    db_port = os.getenv('DB_PORT', '5432')

    # Connect to the database
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
            cur.execute("SELECT role FROM users WHERE id = %s", (user_id,))
            result = cur.fetchone()

            # Return True if the user is a moderator, False otherwise
            return result and result[0] == 'moderator'

    finally:
        conn.close()

# Example usage:
# print(is_user_moderator(1))