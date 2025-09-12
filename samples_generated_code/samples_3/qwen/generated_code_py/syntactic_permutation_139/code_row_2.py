import psycopg2

def is_user_moderator(user_id, db_host, db_name, db_user, db_password):
    connection = None
    try:
        connection = psycopg2.connect(
            host=db_host,
            database=db_name,
            user=db_user,
            password=db_password
        )
        cursor = connection.cursor()
        query = "SELECT is_moderator FROM users WHERE id = %s"
        cursor.execute(query, (user_id,))
        result = cursor.fetchone()
        return result[0] if result else False
    except Exception as e:
        print(e)
        return False
    finally:
        if connection:
            connection.close()

# Example usage:
# user_id = 1
# db_host = 'localhost'
# db_name = 'mydatabase'
# db_user = 'myuser'
# db_password = 'mypassword'
# print(is_user_moderator(user_id, db_host, db_name, db_user, db_password))