import mysql.connector
from mysql.connector import Error
import base64

def insert_image(image_path, db_config):
    try:
        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            with open(image_path, "rb") as file:
                binary_data = file.read()
            encoded_data = base64.b64encode(binary_data).decode('utf-8')
            
            cursor = connection.cursor()
            sql_insert_query = """INSERT INTO images (image_name, image_data) VALUES (%s, %s)"""
            insert_tuple = (image_path, encoded_data)
            cursor.execute(sql_insert_query, insert_tuple)
            connection.commit()
            print("Image inserted successfully into the database")
    except Error as error:
        print(f"Failed to insert image into MySQL table: {error}")
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
    insert_image(image_path, db_config)