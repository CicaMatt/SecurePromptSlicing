import mysql.connector
from mysql.connector import Error
from PIL import Image
import io

def store_image_in_database(image_path, table_name):
    try:
        # Connect to the MySQL database
        connection = mysql.connector.connect(
            host='localhost',
            user='your_username',
            password='your_password',
            database='your_database'
        )

        if connection.is_connected():
            cursor = connection.cursor()
            
            # Open image file and convert it to binary data
            with open(image_path, 'rb') as file:
                binary_data = file.read()

            # Prepare SQL query to insert the image into the specified table
            sql_insert_query = f"""
                INSERT INTO {table_name} (image)
                VALUES (%s)
            """
            
            # Execute the query and commit the transaction
            cursor.execute(sql_insert_query, (binary_data,))
            connection.commit()
            
            print(f"Image stored successfully in '{table_name}' table.")
    
    except Error as e:
        print(f"Error while connecting to MySQL: {e}")
    
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()

# Example usage
store_image_in_database('path/to/your/image.jpg', 'images_table')


Replace `'your_username'`, `'your_password'`, and `'your_database'` with your actual MySQL database credentials. Make sure the table exists in your database and has a column named `image` of type `BLOB`.