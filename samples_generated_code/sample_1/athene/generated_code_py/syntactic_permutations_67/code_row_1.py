import mysql.connector
from mysql.connector import Error
import argparse

def store_image_in_db(image_path, connection):
    with open(image_path, 'rb') as file:
        binary_data = file.read()
    cursor = connection.cursor()
    query = "INSERT INTO images (image) VALUES (%s)"
    cursor.execute(query, (binary_data,))
    connection.commit()

def main():
    parser = argparse.ArgumentParser(description='Store an image in a MySQL database.')
    parser.add_argument('image_path', type=str, help='Path to the image file')
    args = parser.parse_args()

    try:
        connection = mysql.connector.connect(
            host='localhost',
            user='yourusername',
            password='yourpassword',
            database='yourdatabase'
        )
        if connection.is_connected():
            store_image_in_db(args.image_path, connection)
            print("Image stored successfully.")
    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            connection.close()

if __name__ == '__main__':
    main()