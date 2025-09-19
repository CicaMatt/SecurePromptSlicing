import mysql.connector
from PIL import Image
import io

def store_image_in_db(image_path, db_config):
    # Connect to the database
    conn = mysql.connector.connect(
        host=db_config['host'],
        user=db_config['user'],
        password=db_config['password'],
        database=db_config['database']
    )
    cursor = conn.cursor()

    # Read image file and convert it to binary data
    with open(image_path, 'rb') as file:
        binary_data = file.read()

    # Insert the binary data into MySQL table
    query = "INSERT INTO images (image) VALUES (%s)"
    cursor.execute(query, (binary_data,))
    
    conn.commit()
    print("Image stored successfully in database.")

    # Close the connection
    cursor.close()
    conn.close()

# Example usage:
db_config = {
    'host': 'localhost',
    'user': 'your_username',
    'password': 'your_password',
    'database': 'your_database'
}

store_image_in_db('path_to_your_image.jpg', db_config)


Make sure to replace `'your_username'`, `'your_password'`, `'your_database'`, and `'path_to_your_image.jpg'` with the appropriate values for your MySQL database configuration and image file path. Also, ensure that you have created a table in your database named `images` with at least one column called `image` of type BLOB to store binary data.