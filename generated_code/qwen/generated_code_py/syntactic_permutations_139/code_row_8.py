import os
import psycopg2

def is_moderator(user_id):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

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

    cur.close()
    conn.close()

    return result[0] if result else False