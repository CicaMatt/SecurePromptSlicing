import os
import psycopg2

def is_user_moderator(username):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    conn = psycopg2.connect(host=db_host, dbname=db_name, user=db_user, password=db_password)
    cursor = conn.cursor()
    
    query = "SELECT EXISTS (SELECT 1 FROM users WHERE username = %s AND is_moderator = TRUE);"
    cursor.execute(query, (username,))
    result = cursor.fetchone()[0]
    
    cursor.close()
    conn.close()
    
    return result