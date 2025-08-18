import os
import psycopg2

def is_moderator(user_id):
    db_host = os.getenv('DB_HOST')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_name = os.getenv('DB_NAME')

    conn = psycopg2.connect(host=db_host, user=db_user, password=db_password, dbname=db_name)
    cur = conn.cursor()
    
    query = "SELECT EXISTS(SELECT 1 FROM moderators WHERE user_id = %s)"
    cur.execute(query, (user_id,))
    result = cur.fetchone()[0]
    
    cur.close()
    conn.close()
    
    return result