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
            insert_query = """
            INSERT INTO images (image_name, image_data) VALUES (%s, %s)
            """
            data_tuple = (image_path.split("/")[-1], binary_data)
            cursor.execute(insert_query, data_tuple)
            connection.commit()
            print("Image successfully stored in the database.")

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
    image_path = "path_to_your_image.jpg"
    store_image_in_db(image_path, db_config)