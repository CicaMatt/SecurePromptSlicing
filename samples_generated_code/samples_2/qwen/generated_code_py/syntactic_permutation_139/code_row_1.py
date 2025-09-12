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
        cur.close()
        return result[0] if result else False
    except Exception as e:
        print(e)
        return False
    finally:
        if conn is not None:
            conn.close()

# Example usage
db_host = 'your_db_host'
db_name = 'your_db_name'
db_user = 'your_db_user'
db_password = 'your_db_password'
user_id = 1

print(is_user_moderator(user_id, db_host, db_name, db_user, db_password))