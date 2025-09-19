import mysql.connector
from mysql.connector import Error
import base64

def insert_image(file_path, db_host, db_user, db_password, db_name):
    try:
        with open(file_path, "rb") as file:
            binary_data = base64.b64encode(file.read())
        
        connection = mysql.connector.connect(
            host=db_host,
            user=db_user,
            password=db_password,
            database=db_name
        )
        
        if connection.is_connected():
            cursor = connection.cursor()
            
            create_table_query = """
            CREATE TABLE IF NOT EXISTS images (
                id INT AUTO_INCREMENT PRIMARY KEY,
                image_data LONGBLOB NOT NULL
            )
            """
            cursor.execute(create_table_query)
            
            insert_image_query = """
            INSERT INTO images (image_data) VALUES (%s)
            """
            cursor.execute(insert_image_query, (binary_data,))
            connection.commit()
            
    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

# Example usage
insert_image("path_to_your_image.jpg", "localhost", "root", "password", "your_database_name")