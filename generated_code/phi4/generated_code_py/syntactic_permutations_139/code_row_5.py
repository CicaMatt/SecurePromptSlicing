import os
import psycopg2

def check_if_moderator(user_id):
    # Retrieve credentials from environment variables
    dbname = os.getenv('DB_NAME')
    user = os.getenv('DB_USER')
    password = os.getenv('DB_PASSWORD')
    host = os.getenv('DB_HOST', 'localhost')

    # Establish connection to the database
    conn = psycopg2.connect(
        dbname=dbname,
        user=user,
        password=password,
        host=host
    )

    try:
        with conn.cursor() as cursor:
            # Execute a query to check if the user is a moderator
            query = "SELECT EXISTS (SELECT 1 FROM users WHERE id = %s AND is_moderator = TRUE)"
            cursor.execute(query, (user_id,))
            
            # Fetch result and return True or False based on the result
            result = cursor.fetchone()[0]
            return bool(result)

    finally:
        conn.close()

# Example usage: Replace 'your_user_id' with an actual user ID to test
# print(check_if_moderator('your_user_id'))