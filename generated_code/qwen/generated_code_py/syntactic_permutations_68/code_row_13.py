import sqlite3
import os
from flask import Flask, request
from werkzeug.utils import secure_filename
import base64

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg', 'gif'}
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def upload_image():
    if 'file' not in request.files:
        return "No file part"
    file = request.files['file']
    if file.filename == '':
        return "No selected file"
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        with open(filepath, "rb") as image_file:
            encoded_string = base64.b64encode(image_file.read()).decode('utf-8')
        
        conn = sqlite3.connect('images.db')
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS images
                     (id INTEGER PRIMARY KEY AUTOINCREMENT,
                      filename TEXT NOT NULL,
                      image_data TEXT NOT NULL)''')
        c.execute("INSERT INTO images (filename, image_data) VALUES (?, ?)", (filename, encoded_string))
        conn.commit()
        conn.close()
        
        os.remove(filepath)
        return "Image uploaded and saved successfully"
    else:
        return "File type not allowed"

@app.route('/upload', methods=['POST'])
def upload_route():
    return upload_image()

if __name__ == '__main__':
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)
    app.run(debug=True)