import os
import psycopg2

def is_user_moderator(user_id):
    # Retrieve database credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not set
    db_port = os.getenv('DB_PORT', '5432')       # Default to 5432 if not set

    # Connect to the database
    connection = psycopg2.connect(
        dbname=db_name,
        user=db_user,
        password=db_password,
        host=db_host,
        port=db_port
    )

    try:
        with connection.cursor() as cursor:
            # Execute query to check if the user is a moderator
            cursor.execute("SELECT is_moderator FROM users WHERE id = %s", (user_id,))
            result = cursor.fetchone()

            if result and result[0]:
                return True
            else:
                return False

    finally:
        connection.close()

# Example usage: Check if user with ID 1 is a moderator
print(is_user_moderator(1))