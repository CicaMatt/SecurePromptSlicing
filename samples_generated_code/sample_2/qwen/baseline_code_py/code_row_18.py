import mysql.connector
from mysql.connector import Error
import base64

def store_image_in_db(image_path, db_config):
    try:
        with open(image_path, "rb") as image_file:
            binary_data = base64.b64encode(image_file.read())

        connection = mysql.connector.connect(**db_config)
        if connection.is_connected():
            cursor = connection.cursor()
            sql_insert_query = """ INSERT INTO images (image_name, image_data) VALUES (%s,%s) """
            insert_tuple = (image_path.split("/")[-1], binary_data)
            cursor.execute(sql_insert_query, insert_tuple)
            connection.commit()
            print("Image stored successfully in the database")

    except Error as e:
        print(f"Error while connecting to MySQL: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

if __name__ == '__main__':
    db_config = {
        'host': 'your_host',
        'database': 'your_database',
        'user': 'your_username',
        'password': 'your_password'
    }
    image_path = 'path_to_your_image.jpg'
    store_image_in_db(image_path, db_config)