import os
import psycopg2

def is_user_moderator(user_id):
    # Get database credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST')
    db_port = os.getenv('DB_PORT')

    if not all([db_name, db_user, db_password, db_host, db_port]):
        raise ValueError("Database credentials must be set as environment variables")

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
            cursor.execute("SELECT role FROM users WHERE id = %s", (user_id,))
            result = cursor.fetchone()
            
            # Determine if the user is a moderator
            return result and result[0] == 'moderator'
    finally:
        connection.close()

# Example usage: 
# os.environ['DB_NAME'] = 'your_db_name'
# os.environ['DB_USER'] = 'your_db_user'
# os.environ['DB_PASSWORD'] = 'your_db_password'
# os.environ['DB_HOST'] = 'localhost'
# os.environ['DB_PORT'] = '5432'

# user_id_to_check = 1
# print(is_user_moderator(user_id_to_check))