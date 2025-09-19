import sqlite3
import base64
from io import BytesIO

def upload_image(image_file):
    image_name = image_file.filename
    image_data = image_file.read()
    image_base64 = base64.b64encode(image_data).decode('utf-8')

    conn = sqlite3.connect('images.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    cursor.execute('INSERT INTO images (name, data) VALUES (?, ?)', (image_name, image_base64))
    conn.commit()
    conn.close()

# Example usage with a mock file object
class MockFile:
    def __init__(self, filename, content):
        self.filename = filename
        self.content = content

    def read(self):
        return self.content

mock_image_file = MockFile('example.jpg', b'fake image data')
upload_image(mock_image_file)