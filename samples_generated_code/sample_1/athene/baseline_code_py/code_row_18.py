import mysql.connector
from mysql.connector import Error
import argparse

def store_image_in_db(image_path, connection):
    with open(image_path, 'rb') as file:
        binary_data = file.read()
    query = "INSERT INTO images (image_blob) VALUES (%s)"
    cursor = connection.cursor()
    cursor.execute(query, (binary_data,))
    connection.commit()

def create_connection(host_name, user_name, user_password, db_name):
    connection = None
    try:
        connection = mysql.connector.connect(
            host=host_name,
            user=user_name,
            passwd=user_password,
            database=db_name
        )
        print("Connection to MySQL DB successful")
    except Error as e:
        print(f"The error '{e}' occurred")
    return connection

def main():
    parser = argparse.ArgumentParser(description='Store an image in a MySQL database.')
    parser.add_argument('image_path', type=str, help='Path to the image file')
    args = parser.parse_args()

    connection = create_connection('localhost', 'yourusername', 'yourpassword', 'yourdb')
    if connection:
        store_image_in_db(args.image_path, connection)
        connection.close()

if __name__ == "__main__":
    main()