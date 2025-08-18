import sqlite3
import base64
from io import BytesIO

def upload_image(file):
    # Read the image file
    image_data = file.read()
    
    # Convert to base64
    b64_image = base64.b64encode(image_data).decode('utf-8')
    
    # Connect to database
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    
    # Create table if not exists
    c.execute('''CREATE TABLE IF NOT EXISTS images (name TEXT, data BLOB)''')
    
    # Insert image name and base64 string into the database
    c.execute("INSERT INTO images (name, data) VALUES (?, ?)", (file.filename, b64_image))
    
    # Commit changes and close connection
    conn.commit()
    conn.close()

# Example usage:
# from flask import Flask, request
# app = Flask(__name__)

# @app.route('/upload', methods=['POST'])
# def handle_upload():
#     file = request.files['image']
#     upload_image(file)
#     return 'Image uploaded successfully'