import os
import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    file_name = os.path.basename(image_path)
    
    # Assuming a database connection is already established and 'cursor' is a valid cursor object
    query = """
        INSERT INTO images (image_name, image_data) 
        VALUES (%s, %s);
    """
    data = (file_name, encoded_string)
    
    try:
        cursor.execute(query, data)
        db_connection.commit()
        print("Image uploaded successfully.")
    except Exception as e:
        db_connection.rollback()
        print(f"An error occurred: {e}")

# Example usage
# Assume 'cursor' and 'db_connection' are already defined and connected to your database.
# upload_image('path/to/your/image.jpg')