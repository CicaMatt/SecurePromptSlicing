import base64

def upload_image(image_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    image_name = image_path.split("/")[-1]
    insert_into_database(image_name, encoded_string)

def insert_into_database(image_name, base64_string):
    # Example of inserting into a database
    import sqlite3
    
    connection = sqlite3.connect('images.db')
    cursor = connection.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data TEXT)''')
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_name, base64_string))
    connection.commit()
    connection.close()

# Example usage
upload_image('path/to/your/image.jpg')