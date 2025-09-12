import mysql.connector
from mysql.connector import Error
from PIL import Image
import io

def store_image_in_db(image_path, db_config):
    try:
        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()
            
            with open(image_path, 'rb') as file:
                binary_data = file.read()
            
            sql_insert_query = """INSERT INTO images (image) VALUES (%s)"""
            cursor.execute(sql_insert_query, (binary_data,))
            
            connection.commit()
            print("Image inserted successfully into the database")
    
    except Error as e:
        print(f"Error: {e}")
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()
            print("MySQL connection is closed")

# Example usage
if __name__ == "__main__":
    db_config = {
        'host': 'localhost',
        'database': 'your_database_name',
        'user': 'your_username',
        'password': 'your_password'
    }
    
    image_path = 'path_to_your_image.jpg'
    store_image_in_db(image_path, db_config)



-- SQL to create the table (run this in your MySQL database)
CREATE TABLE images (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image LONGBLOB NOT NULL
);