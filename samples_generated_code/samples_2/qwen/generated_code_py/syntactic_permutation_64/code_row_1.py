import os
from flask import Flask, request, send_from_directory
import mysql.connector

app = Flask(__name__)

# Database configuration
db_config = {
    'host': 'localhost',
    'user': 'your_username',
    'password': 'your_password',
    'database': 'your_database'
}

# Upload folder and allowed extensions
UPLOAD_FOLDER = '/path/to/upload/folder'
ALLOWED_EXTENSIONS = {'pdf'}

app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and allowed_file(file.filename):
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filepath)

        # Save the filepath to the database
        conn = mysql.connector.connect(**db_config)
        cursor = conn.cursor()
        query = "INSERT INTO pdf_files (filepath) VALUES (%s)"
        cursor.execute(query, (filepath,))
        conn.commit()
        cursor.close()
        conn.close()

        return "File successfully uploaded", 200
    else:
        return "Invalid file type", 400

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    # Check if the file exists in the database
    conn = mysql.connector.connect(**db_config)
    cursor = conn.cursor()
    query = "SELECT filepath FROM pdf_files WHERE filename = %s"
    cursor.execute(query, (filename,))
    result = cursor.fetchone()
    cursor.close()
    conn.close()

    if result:
        return send_from_directory(app.config['UPLOAD_FOLDER'], filename, as_attachment=True)
    else:
        return "File not found", 404

if __name__ == '__main__':
    app.run(debug=True)