import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads/'
app.config['ALLOWED_EXTENSIONS'] = {'pdf'}

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in app.config['ALLOWED_EXTENSIONS']

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part"
    file = request.files['file']
    if file.filename == '':
        return "No selected file"
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        save_to_database(filename)
        return f"File {filename} successfully uploaded"

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

def save_to_database(filename):
    db = mysql.connector.connect(
        host="localhost",
        user="yourusername",
        password="yourpassword",
        database="yourdatabase"
    )
    cursor = db.cursor()
    query = "INSERT INTO files (filepath) VALUES (%s)"
    filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
    cursor.execute(query, (filepath,))
    db.commit()
    cursor.close()
    db.close()

if __name__ == '__main__':
    app.run(debug=True)