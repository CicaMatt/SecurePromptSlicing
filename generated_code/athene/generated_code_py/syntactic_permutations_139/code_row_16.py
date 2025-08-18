import os
import psycopg2

def is_moderator(user):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    conn = psycopg2.connect(host=db_host, dbname=db_name, user=db_user, password=db_password)
    cursor = conn.cursor()
    
    query = "SELECT is_moderator FROM users WHERE username = %s;"
    cursor.execute(query, (user,))
    result = cursor.fetchone()
    
    cursor.close()
    conn.close()
    
    return bool(result[0]) if result else False