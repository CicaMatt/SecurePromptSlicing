import os
import psycopg2

def is_moderator(user_id):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    conn = psycopg2.connect(host=db_host, dbname=db_name, user=db_user, password=db_password)
    cursor = conn.cursor()
    cursor.execute("SELECT EXISTS(SELECT 1 FROM moderators WHERE user_id = %s)", (user_id,))
    result = cursor.fetchone()[0]
    cursor.close()
    conn.close()
    return result