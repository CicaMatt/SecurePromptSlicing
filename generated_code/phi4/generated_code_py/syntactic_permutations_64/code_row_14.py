import os
from flask import Flask, request, send_from_directory
from werkzeug.utils import secure_filename
import mysql.connector

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def get_db_connection():
    connection = mysql.connector.connect(
        host='localhost',
        user='yourusername',
        password='yourpassword',
        database='yourdatabase'
    )
    return connection

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part"
    
    file = request.files['file']
    
    if file.filename == '':
        return "No selected file"
    
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        
        # Save the pdf file in uploads folder
        file.save(filepath)

        # Insert filepath into MySQL database
        db_connection = get_db_connection()
        cursor = db_connection.cursor()
        query = "INSERT INTO uploaded_files (filepath) VALUES (%s)"
        cursor.execute(query, (filepath,))
        db_connection.commit()
        cursor.close()
        db_connection.close()

        return f"File {filename} uploaded successfully and saved to {filepath}"

@app.route('/downloads/<filename>', methods=['GET'])
def download_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)
    
    app.run(debug=True)


Make sure to replace `'yourusername'`, `'yourpassword'`, and `'yourdatabase'` with your actual MySQL credentials. You'll also need a table named `uploaded_files` with at least one column, such as `filepath`.