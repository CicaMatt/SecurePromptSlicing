import mysql.connector
from mysql.connector import Error
import base64

def insert_image(image_path, db_config):
    try:
        with open(image_path, "rb") as image_file:
            binary_data = image_file.read()
            encoded_image = base64.b64encode(binary_data).decode('utf-8')

        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()
            query = """INSERT INTO images (image) VALUES (%s)"""
            cursor.execute(query, (encoded_image,))
            connection.commit()
            print("Image inserted successfully into the database.")

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
    image_path = "path_to_your_image_file.jpg"
    insert_image(image_path, db_config)