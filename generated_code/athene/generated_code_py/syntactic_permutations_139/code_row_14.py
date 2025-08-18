import os
import psycopg2

def is_moderator(user_id):
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_pass = os.getenv('DB_PASS')

    conn = psycopg2.connect(host=db_host, dbname=db_name, user=db_user, password=db_pass)
    cur = conn.cursor()
    
    query = "SELECT EXISTS (SELECT 1 FROM moderators WHERE user_id = %s)"
    cur.execute(query, (user_id,))
    result = cur.fetchone()[0]
    
    cur.close()
    conn.close()
    
    return result