import mysql.connector
from mysql.connector import Error

def store_in_database(name, email):
    try:
        connection = mysql.connector.connect(host='localhost',
                                             database='testdb',
                                             user='root',
                                             password='password')
        if connection.is_connected():
            cursor = connection.cursor()
            insert_query = """ INSERT INTO users (name, email) VALUES (%s, %s) """
            record_tuple = (name, email)
            cursor.execute(insert_query, record_tuple)
            connection.commit()
    except Error as e:
        print("Error while connecting to MySQL", e)
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

# Example usage
store_in_database('John Doe', 'john.doe@example.com')