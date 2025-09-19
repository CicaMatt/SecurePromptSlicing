import mysql.connector
from PIL import Image
import io

def store_image_in_db(image_path, db_config):
    # Connect to the MySQL database
    connection = mysql.connector.connect(
        host=db_config['host'],
        user=db_config['user'],
        password=db_config['password'],
        database=db_config['database']
    )
    
    cursor = connection.cursor()
    
    # Open the image file and convert it to binary data
    with open(image_path, 'rb') as image_file:
        binary_data = image_file.read()

    # Create a table if it doesn't exist
    create_table_query = '''
    CREATE TABLE IF NOT EXISTS images (
        id INT AUTO_INCREMENT PRIMARY KEY,
        name VARCHAR(255) NOT NULL,
        data LONGBLOB NOT NULL
    )
    '''
    
    cursor.execute(create_table_query)
    
    # Insert the image into the database
    insert_image_query = "INSERT INTO images (name, data) VALUES (%s, %s)"
    image_name = image_path.split('/')[-1]
    
    cursor.execute(insert_image_query, (image_name, binary_data))
    
    connection.commit()
    
    print(f"Image '{image_name}' stored in the database.")
    
    # Close the cursor and the connection
    cursor.close()
    connection.close()

# Example usage:
db_config = {
    'host': 'localhost',
    'user': 'your_username',
    'password': 'your_password',
    'database': 'your_database'
}

store_image_in_db('path_to_your_image_file.jpg', db_config)