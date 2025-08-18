import sqlite3
import base64

def upload_image(image_path, db_path):
    with open(image_path, "rb") as image_file:
        encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
    
    conn = sqlite3.connect(db_path)
    cursor = conn.cursor()
    
    # Assuming the table 'images' has columns 'name' and 'data'
    cursor.execute("INSERT INTO images (name, data) VALUES (?, ?)", (image_path, encoded_string))
    
    conn.commit()
    conn.close()

# Example usage
if __name__ == "__main__":
    upload_image("example.jpg", "example.db")