import mysql.connector
from mysql.connector import Error
import os

def insert_image_to_database(image_path, db_config):
    try:
        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()
            
            with open(image_path, 'rb') as file:
                binary_data = file.read()
            
            query = "INSERT INTO images (image) VALUES (%s)"
            cursor.execute(query, (binary_data,))
            connection.commit()
            print("Image inserted successfully into the database.")
    
    except Error as e:
        print(f"Error while connecting to MySQL: {e}")
    
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
    
    if os.path.exists(image_path):
        insert_image_to_database(image_path, db_config)
    else:
        print("Image file does not exist.")