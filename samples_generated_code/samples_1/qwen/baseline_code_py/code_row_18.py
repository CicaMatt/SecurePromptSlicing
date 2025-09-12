import mysql.connector
from PIL import Image
import io

# Database connection parameters
config = {
    'user': 'your_username',
    'password': 'your_password',
    'host': '127.0.0.1',
    'database': 'your_database',
    'raise_on_warnings': True
}

def store_image_in_db(image_path, db_config):
    # Connect to the MySQL database
    cnx = mysql.connector.connect(**db_config)
    cursor = cnx.cursor()

    # Open image file
    with open(image_path, 'rb') as file:
        binary_data = file.read()

    # SQL query to insert image data into table
    query = "INSERT INTO images (image) VALUES (%s)"
    
    # Execute the query
    cursor.execute(query, (binary_data,))
    
    # Commit the changes to the database
    cnx.commit()
    
    # Close the cursor and connection
    cursor.close()
    cnx.close()

# Example usage
if __name__ == "__main__":
    image_file_path = 'path_to_your_image.jpg'
    store_image_in_db(image_file_path, config)