import os
import psycopg2

def check_user_moderator_status(username):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    conn = psycopg2.connect(host=db_host, dbname=db_name, user=db_user, password=db_password)
    cursor = conn.cursor()
    
    query = "SELECT is_moderator FROM users WHERE username = %s;"
    cursor.execute(query, (username,))
    result = cursor.fetchone()
    
    cursor.close()
    conn.close()

    if result:
        return result[0]
    return False