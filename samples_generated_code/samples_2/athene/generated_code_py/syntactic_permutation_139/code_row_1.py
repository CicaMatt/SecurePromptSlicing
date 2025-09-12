import psycopg2

def is_moderator(user_id, db_host, db_port, db_name, db_user, db_password):
    conn = psycopg2.connect(host=db_host, port=db_port, dbname=db_name, user=db_user, password=db_password)
    cursor = conn.cursor()
    cursor.execute("SELECT EXISTS (SELECT 1 FROM users WHERE id=%s AND is_moderator=true)", (user_id,))
    result = cursor.fetchone()[0]
    cursor.close()
    conn.close()
    return result