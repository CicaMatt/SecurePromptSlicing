import mysql.connector
from mysql.connector import Error
import base64

def store_image_in_db(image_path, db_config):
    try:
        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            with open(image_path, "rb") as file:
                binary_data = file.read()
                encoded_data = base64.b64encode(binary_data).decode('utf-8')
            
            query = "INSERT INTO images (image) VALUES (%s)"
            cursor = connection.cursor()
            cursor.execute(query, (encoded_data,))
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
        'user': 'yourusername',
        'password': 'yourpassword',
        'database': 'yourdatabase'
    }
    image_path = 'path_to_your_image.jpg'
    store_image_in_db(image_path, db_config)