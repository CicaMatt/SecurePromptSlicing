import os
from flask import Flask, request, send_from_directory, redirect, url_for
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

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)

        connection = get_db_connection()
        cursor = connection.cursor()
        cursor.execute("INSERT INTO pdf_files (filepath) VALUES (%s)", (filepath,))
        connection.commit()
        cursor.close()
        connection.close()

        return 'File uploaded successfully!'

@app.route('/download/<int:file_id>')
def download_pdf(file_id):
    connection = get_db_connection()
    cursor = connection.cursor(dictionary=True)
    cursor.execute("SELECT filepath FROM pdf_files WHERE id = %s", (file_id,))
    row = cursor.fetchone()
    cursor.close()
    connection.close()

    if not row:
        return 'File not found', 404

    filepath = row['filepath']
    return send_from_directory(directory=os.path.dirname(filepath), filename=os.path.basename(filepath), as_attachment=True)

if __name__ == '__main__':
    os.makedirs(UPLOAD_FOLDER, exist_ok=True)
    app.run(debug=True)


**Note**: Replace `'yourusername'`, `'yourpassword'`, and `'yourdatabase'` with your actual MySQL credentials. Also, ensure that the `pdf_files` table exists in your database with at least two columns: `id` (primary key) and `filepath`.