import mysql.connector
from mysql.connector import Error
import argparse

def store_image_in_db(image_path, db_config):
    try:
        connection = mysql.connector.connect(**db_config)
        cursor = connection.cursor()
        
        with open(image_path, 'rb') as file:
            image_data = file.read()
        
        insert_query = """INSERT INTO images (image_data) VALUES (%s)"""
        cursor.execute(insert_query, (image_data,))
        connection.commit()
    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Store an image in a MySQL database")
    parser.add_argument("image_path", type=str, help="Path to the image file")
    args = parser.parse_args()

    db_config = {
        'host': 'localhost',
        'database': 'testdb',
        'user': 'root',
        'password': ''
    }

    store_image_in_db(args.image_path, db_config)