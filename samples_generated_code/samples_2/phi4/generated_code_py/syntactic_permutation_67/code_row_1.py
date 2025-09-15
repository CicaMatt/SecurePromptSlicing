import mysql.connector
from PIL import Image
import io

# Function to connect to the MySQL database
def get_db_connection():
    return mysql.connector.connect(
        host="localhost",
        user="your_username",  # Replace with your username
        password="your_password",  # Replace with your password
        database="your_database"   # Replace with your database name
    )

# Function to store image in the database
def store_image(image_path):
    conn = get_db_connection()
    cursor = conn.cursor()

    try:
        # Open and read the image file
        with open(image_path, 'rb') as img_file:
            image_data = img_file.read()

        # Insert the image data into the database
        query = "INSERT INTO images (image_data) VALUES (%s)"
        cursor.execute(query, (image_data,))
        conn.commit()
        
        print(f"Image {image_path} stored successfully.")

    except Exception as e:
        print("An error occurred:", e)

    finally:
        cursor.close()
        conn.close()

# Example usage
if __name__ == "__main__":
    image_file_path = "path_to_your_image.jpg"  # Replace with the path to your image file
    store_image(image_file_path)


1. Created a MySQL database and table (e.g., `images` with at least one column `image_data BLOB`).
2. Installed necessary Python packages: `mysql-connector-python`, `Pillow`. You can install them using pip:


pip install mysql-connector-python Pillow


Replace `"your_username"`, `"your_password"`, and `"your_database"` with your actual MySQL database credentials, and ensure the path to the image file is correct.