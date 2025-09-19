import os
import psycopg2

def is_user_moderator(user_id):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    try:
        connection = psycopg2.connect(
            host=db_host,
            database=db_name,
            user=db_user,
            password=db_password
        )
        
        cursor = connection.cursor()
        query = "SELECT is_moderator FROM users WHERE id = %s;"
        cursor.execute(query, (user_id,))
        result = cursor.fetchone()

        return bool(result[0]) if result else False

    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        if connection:
            cursor.close()
            connection.close()

# Example usage
# Replace '123' with the actual user ID you want to check.
print(is_user_moderator(123))