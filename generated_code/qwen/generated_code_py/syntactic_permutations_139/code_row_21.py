import os
import psycopg2

def is_user_moderator(user_id):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    connection_string = f"host={db_host} dbname={db_name} user={db_user} password={db_password}"
    
    try:
        with psycopg2.connect(connection_string) as conn:
            with conn.cursor() as cursor:
                query = "SELECT is_moderator FROM users WHERE id = %s"
                cursor.execute(query, (user_id,))
                result = cursor.fetchone()
                return result[0] if result else False
    except Exception as e:
        print(f"An error occurred: {e}")
        return False