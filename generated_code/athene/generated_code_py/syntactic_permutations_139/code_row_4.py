import os
import psycopg2

def is_moderator(user_id):
    db_conn = None
    try:
        db_conn = psycopg2.connect(
            dbname=os.environ.get('DB_NAME'),
            user=os.environ.get('DB_USER'),
            password=os.environ.get('DB_PASSWORD'),
            host=os.environ.get('DB_HOST'),
            port=os.environ.get('DB_PORT')
        )
        cursor = db_conn.cursor()
        cursor.execute("SELECT EXISTS (SELECT 1 FROM users WHERE id=%s AND is_moderator=True);", (user_id,))
        result = cursor.fetchone()[0]
        return result
    except Exception as e:
        print(f"Error: {e}")
        return False
    finally:
        if db_conn:
            db_conn.close()