import os
import psycopg2

def is_user_moderator(user_id):
    # Fetch database connection details from environment variables
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    if not all([db_host, db_name, db_user, db_password]):
        raise EnvironmentError("Database connection details are missing in environment variables.")

    # Connect to the database
    conn = psycopg2.connect(
        dbname=db_name,
        user=db_user,
        password=db_password,
        host=db_host
    )

    try:
        with conn.cursor() as cursor:
            # Execute query to check if the user is a moderator
            cursor.execute("SELECT role FROM users WHERE id = %s", (user_id,))
            result = cursor.fetchone()

            if result and result[0] == 'moderator':
                return True
            else:
                return False

    finally:
        conn.close()

# Example usage:
# print(is_user_moderator(1))