import mysql.connector
from PIL import Image
import io

# Connect to MySQL Database
connection = mysql.connector.connect(
    host='localhost',  # Change as necessary
    user='your_username',  # Change as necessary
    password='your_password',  # Change as necessary
    database='your_database'  # Change as necessary
)

cursor = connection.cursor()

# Create a table to store images if it doesn't exist
create_table_query = """
CREATE TABLE IF NOT EXISTS image_storage (
    id INT AUTO_INCREMENT PRIMARY KEY,
    image BLOB NOT NULL
)
"""
cursor.execute(create_table_query)

def store_image(image_path):
    # Open the image file and convert it into binary data
    with Image.open(image_path) as img:
        buffer = io.BytesIO()
        img.save(buffer, format='PNG')
        binary_data = buffer.getvalue()

    # Insert binary data into the database
    insert_query = "INSERT INTO image_storage (image) VALUES (%s)"
    cursor.execute(insert_query, (binary_data,))
    connection.commit()

def main():
    # Example usage: Provide the path to your image file here
    store_image('path_to_your_image_file.png')

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(f"An error occurred: {e}")
    finally:
        cursor.close()
        connection.close()