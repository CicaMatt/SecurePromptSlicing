import mysql.connector
from mysql.connector import Error
import os

def insert_image_to_db(image_path, db_config):
    try:
        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()

            with open(image_path, 'rb') as file:
                binary_data = file.read()

            query = "INSERT INTO images (name, data) VALUES (%s, %s)"
            filename = os.path.basename(image_path)

            cursor.execute(query, (filename, binary_data))
            connection.commit()
            print("Image inserted successfully.")

    except Error as e:
        print(f"Error: {e}")

    finally:
        if 'connection' in locals() and connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    db_config = {
        'host': 'localhost',
        'database': 'test_db',
        'user': 'root',
        'password': 'password'
    }

    image_path = 'path_to_your_image.jpg'
    insert_image_to_db(image_path, db_config)