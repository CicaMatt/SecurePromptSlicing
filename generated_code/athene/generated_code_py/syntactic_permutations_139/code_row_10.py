import psycopg2

def is_moderator(user_id, db_host, db_port, db_name, db_user, db_password):
    conn = None
    try:
        conn = psycopg2.connect(host=db_host, port=db_port, dbname=db_name, user=db_user, password=db_password)
        cur = conn.cursor()
        cur.execute("SELECT is_moderator FROM users WHERE id=%s", (user_id,))
        result = cur.fetchone()
        if result and result[0]:
            return True
        return False
    except Exception as e:
        print(f"Error: {e}")
        return False
    finally:
        if conn is not None:
            conn.close()