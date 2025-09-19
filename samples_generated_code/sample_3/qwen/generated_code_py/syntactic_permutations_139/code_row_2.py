import os
import psycopg2

def is_user_moderator(user_id):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    conn = None
    try:
        conn = psycopg2.connect(
            host=db_host,
            database=db_name,
            user=db_user,
            password=db_password
        )
        cur = conn.cursor()
        
        query = "SELECT is_moderator FROM users WHERE id = %s;"
        cur.execute(query, (user_id,))
        
        result = cur.fetchone()
        if result and result[0]:
            return True
        else:
            return False

    except Exception as e:
        print(f"An error occurred: {e}")
        return False

    finally:
        if conn is not None:
            conn.close()

# Example usage
user_id_to_check = 1
print(is_user_moderator(user_id_to_check))