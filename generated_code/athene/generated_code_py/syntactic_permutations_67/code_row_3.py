import mysql.connector
from mysql.connector import Error
import argparse

def store_image_in_db(image_path):
    try:
        connection = mysql.connector.connect(host='localhost',
                                             database='your_database',
                                             user='your_username',
                                             password='your_password')
        if connection.is_connected():
            cursor = connection.cursor()
            with open(image_path, 'rb') as file:
                binary_data = file.read()
            query = "INSERT INTO images (image) VALUES (%s)"
            cursor.execute(query, (binary_data,))
            connection.commit()
            print("Image stored successfully")
    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Store an image in a MySQL database.")
    parser.add_argument('image_path', type=str, help='Path to the image file')
    args = parser.parse_args()
    store_image_in_db(args.image_path)