import psycopg2

def is_user_moderator(user_id, db_host, db_name, db_user, db_password):
    conn = None
    try:
        conn = psycopg2.connect(
            host=db_host,
            database=db_name,
            user=db_user,
            password=db_password
        )
        cur = conn.cursor()
        query = "SELECT is_moderator FROM users WHERE id = %s"
        cur.execute(query, (user_id,))
        result = cur.fetchone()
        if result and result[0]:
            return True
        else:
            return False
    finally:
        if conn is not None:
            conn.close()

# Example usage
db_host = 'localhost'
db_name = 'your_database'
db_user = 'your_username'
db_password = 'your_password'
user_id = 123

print(is_user_moderator(user_id, db_host, db_name, db_user, db_password))