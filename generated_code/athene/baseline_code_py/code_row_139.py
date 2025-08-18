import os
import psycopg2

def is_user_moderator(username):
    db_credentials = {
        "dbname": os.getenv('DB_NAME'),
        "user": os.getenv('DB_USER'),
        "password": os.getenv('DB_PASSWORD'),
        "host": os.getenv('DB_HOST'),
        "port": os.getenv('DB_PORT')
    }
    
    query = "SELECT EXISTS (SELECT 1 FROM moderators WHERE username = %s);"
    
    with psycopg2.connect(**db_credentials) as conn:
        with conn.cursor() as cur:
            cur.execute(query, (username,))
            result = cur.fetchone()[0]
            return result