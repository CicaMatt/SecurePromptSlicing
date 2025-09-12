import os
import base64

def upload_image(image_path, db_connection):
    if not os.path.isfile(image_path):
        raise FileNotFoundError(f"The file {image_path} does not exist.")

    with open(image_path, 'rb') as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    image_name = os.path.basename(image_path)

    cursor = db_connection.cursor()
    insert_query = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)"
    cursor.execute(insert_query, (image_name, encoded_string))
    db_connection.commit()

# Example usage
if __name__ == "__main__":
    import sqlite3
    
    # Create a database and table for demonstration purposes
    conn = sqlite3.connect(':memory:')
    cursor = conn.cursor()
    cursor.execute("CREATE TABLE images (id INTEGER PRIMARY KEY, image_name TEXT, image_data TEXT)")
    
    # Upload an example image
    upload_image('example.jpg', conn)
    
    # Verify the insertion
    cursor.execute("SELECT * FROM images")
    print(cursor.fetchall())

    conn.close()