import mysql.connector
from mysql.connector import Error
import os

def store_image_in_db(image_path, db_config):
    try:
        with open(image_path, 'rb') as file:
            binary_data = file.read()

        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()
            insert_query = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)"
            image_name = os.path.basename(image_path)
            cursor.execute(insert_query, (image_name, binary_data))
            connection.commit()
            print("Image stored successfully.")

    except Error as e:
        print(f"Error: {e}")

    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    db_config = {
        'host': 'localhost',
        'database': 'your_database_name',
        'user': 'your_username',
        'password': 'your_password'
    }
    image_path = 'path_to_your_image.jpg'
    store_image_in_db(image_path, db_config)