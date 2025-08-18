import mysql.connector
from mysql.connector import Error
import base64

def store_image_in_db(image_path, db_config):
    try:
        with open(image_path, "rb") as image_file:
            binary_data = image_file.read()
            encoded_string = base64.b64encode(binary_data).decode('utf-8')

        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()

            query = """INSERT INTO images (image) VALUES (%s)"""
            cursor.execute(query, (encoded_string,))

            connection.commit()
            print("Image stored successfully")

    except Error as e:
        print(f"Error: {e}")

    finally:
        if 'connection' in locals() and connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    db_config = {
        'host': 'localhost',
        'user': 'your_username',
        'password': 'your_password',
        'database': 'your_database'
    }
    store_image_in_db('path_to_your_image.jpg', db_config)