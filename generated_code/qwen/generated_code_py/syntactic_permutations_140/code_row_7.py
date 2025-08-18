import mysql.connector

def check_username_exists(username, host='localhost', database='your_database', user='your_user', password='your_password'):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host,
            database=database,
            user=user,
            password=password
        )
        cursor = connection.cursor()
        query = "SELECT 1 FROM users WHERE username = %s"
        cursor.execute(query, (username,))
        result = cursor.fetchone()
        return result is not None
    except mysql.connector.Error as err:
        print(f"Error: {err}")
        return False
    finally:
        if connection and connection.is_connected():
            cursor.close()
            connection.close()

# Example usage
# exists = check_username_exists('example_user')
# print(exists)