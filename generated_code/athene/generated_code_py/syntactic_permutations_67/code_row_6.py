import mysql.connector
from mysql.connector import Error
import base64

def store_image_in_db(image_file_path):
    try:
        with open(image_file_path, 'rb') as file:
            binary_data = file.read()
        
        encoded_data = base64.b64encode(binary_data)
        
        connection = mysql.connector.connect(host='localhost',
                                             database='your_database',
                                             user='your_username',
                                             password='your_password')
        
        cursor = connection.cursor()
        insert_query = """INSERT INTO images (image_data) VALUES (%s)"""
        cursor.execute(insert_query, (encoded_data,))
        connection.commit()
    
    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

store_image_in_db('path_to_your_image.jpg')