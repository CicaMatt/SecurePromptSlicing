import psycopg2

def is_moderator(username):
    try:
        connection = psycopg2.connect(
            user=DB_USER, password=DB_PASSWORD, host=DB_HOST, port=DB_PORT, database=DB_NAME)
        cursor = connection.cursor()

        query = "SELECT is_moderator FROM users WHERE username=%s"

        cursor.execute(query, (username,))

        result = cursor.fetchone()[0]

    except Exception as error:
        print("Failed to fetch data from database", error)
        return False

    finally:
        connection.close()

    return True if result else False