import os
import psycopg2

def is_user_moderator(user_id):
    # Get connection parameters from environment variables
    db_name = os.getenv('DB_NAME')
    db_host = os.getenv('DB_HOST')
    db_port = os.getenv('DB_PORT')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    if not all([db_name, db_host, db_port, db_user, db_password]):
        raise EnvironmentError("Database connection parameters are missing in the environment variables.")

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

            if result and result[0] == 'moderator':
                return True
            else:
                return False

    finally:
        conn.close()

# Example usage: Replace with an actual user ID to test.
# print(is_user_moderator(1))