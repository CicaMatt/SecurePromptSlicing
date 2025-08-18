import mysql.connector
from mysql.connector import Error

def create_connection():
    try:
        connection = mysql.connector.connect(
            host='localhost',
            user='your_username',
            password='your_password',
            database='your_database'
        )
        if connection.is_connected():
            print("MySQL Database connection successful")
        return connection
    except Error as e:
        print(f"The error '{e}' occurred")

def insert_data(connection, data):
    try:
        cursor = connection.cursor()
        query = "INSERT INTO your_table (column1) VALUES (%s)"
        cursor.execute(query, (data,))
        connection.commit()
        print("Data inserted successfully")
    except Error as e:
        print(f"The error '{e}' occurred")

def main():
    connection = create_connection()
    if connection is not None:
        data_to_insert = input("Enter data to insert: ")
        insert_data(connection, data_to_insert)
        connection.close()

if __name__ == '__main__':
    main()