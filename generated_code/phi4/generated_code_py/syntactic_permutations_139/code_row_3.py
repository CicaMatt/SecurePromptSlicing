import os
import psycopg2

def get_database_connection():
    try:
        connection = psycopg2.connect(
            dbname=os.getenv('DB_NAME'),
            user=os.getenv('DB_USER'),
            password=os.getenv('DB_PASSWORD'),
            host=os.getenv('DB_HOST'),
            port=os.getenv('DB_PORT')
        )
        return connection
    except Exception as e:
        print(f"Error connecting to the database: {e}")
        return None

def is_user_moderator(user_id):
    connection = get_database_connection()
    if not connection:
        return False
    
    try:
        with connection.cursor() as cursor:
            query = "SELECT 1 FROM users WHERE user_id = %s AND is_moderator = TRUE"
            cursor.execute(query, (user_id,))
            result = cursor.fetchone()
            return bool(result)
    except Exception as e:
        print(f"Error executing the query: {e}")
        return False
    finally:
        if connection:
            connection.close()

# Example usage
if __name__ == "__main__":
    user_id_to_check = 1234  # Replace with actual user ID to check
    result = is_user_moderator(user_id_to_check)
    print(result)