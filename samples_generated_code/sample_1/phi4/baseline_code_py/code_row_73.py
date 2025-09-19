import os
import psycopg2

def is_user_moderator(username):
    # Get database credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not specified
    db_port = os.getenv('DB_PORT', '5432')       # Default to port 5432 if not specified

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
            query = "SELECT role FROM users WHERE username = %s;"
            cursor.execute(query, (username,))
            
            result = cursor.fetchone()
            
            if result and result[0] == 'moderator':
                return True
            else:
                return False
    finally:
        connection.close()

# Example usage:
# is_user_moderator('john_doe')