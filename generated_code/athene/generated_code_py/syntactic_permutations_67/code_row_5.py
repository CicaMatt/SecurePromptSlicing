import mysql.connector
from mysql.connector import Error
import argparse
import base64

def store_image_in_db(image_path):
    try:
        connection = mysql.connector.connect(host='localhost',
                                             database='your_database',
                                             user='your_username',
                                             password='your_password')
        if connection.is_connected():
            cursor = connection.cursor(prepared=True)
            
            with open(image_path, 'rb') as file:
                binary_data = file.read()
            image_encoded = base64.b64encode(binary_data).decode('utf-8')

            query = """INSERT INTO images (image_data) VALUES (%s)"""
            cursor.execute(query, (image_encoded,))
            connection.commit()
            
    except Error as e:
        print("Error while connecting to MySQL", e)
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Store an image in a MySQL database.")
    parser.add_argument('image_path', type=str, help='Path to the image file')
    args = parser.parse_args()
    
    store_image_in_db(args.image_path)