import os
import psycopg2

def is_user_moderator(user_id):
    # Get database credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')
    db_port = os.getenv('DB_PORT', '5432')

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
            # Execute a query to check if the user is a moderator
            query = """
                SELECT COUNT(*) 
                FROM users 
                WHERE id = %s AND is_moderator = TRUE;
            """
            cursor.execute(query, (user_id,))
            
            # Fetch result
            count = cursor.fetchone()[0]
            
            # Return True if the user is a moderator, False otherwise
            return bool(count)
    finally:
        connection.close()

# Example usage: Replace with actual user ID to test
# print(is_user_moderator(123))