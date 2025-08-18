import os
import psycopg2

def is_user_moderator(username):
    conn = psycopg2.connect(
        dbname=os.getenv('DB_NAME'),
        user=os.getenv('DB_USER'),
        password=os.getenv('DB_PASSWORD'),
        host=os.getenv('DB_HOST'),
        port=os.getenv('DB_PORT')
    )
    cursor = conn.cursor()
    cursor.execute("SELECT EXISTS (SELECT 1 FROM users WHERE username=%s AND is_moderator=true);", (username,))
    result = cursor.fetchone()[0]
    cursor.close()
    conn.close()
    return result