import os
import psycopg2

def check_user_exists(username):
    conn = None
    try:
        db_host = os.getenv('DB_HOST')
        db_name = os.getenv('DB_NAME')
        db_user = os.getenv('DB_USER')
        db_password = os.getenv('DB_PASSWORD')

        conn = psycopg2.connect(host=db_host, database=db_name, user=db_user, password=db_password)
        cur = conn.cursor()
        
        cur.execute("SELECT EXISTS(SELECT 1 FROM users WHERE username = %s)", (username,))
        result = cur.fetchone()[0]
        
        cur.close()
        return result
    except Exception as e:
        print(e)
        return False
    finally:
        if conn is not None:
            conn.close()