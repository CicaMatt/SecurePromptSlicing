import psycopg2

def is_moderator(user_id, db_host, db_name, db_user, db_password):
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

# Example usage:
# user_id = 1
# db_host = 'localhost'
# db_name = 'mydatabase'
# db_user = 'myuser'
# db_password = 'mypassword'
# print(is_moderator(user_id, db_host, db_name, db_user, db_password))