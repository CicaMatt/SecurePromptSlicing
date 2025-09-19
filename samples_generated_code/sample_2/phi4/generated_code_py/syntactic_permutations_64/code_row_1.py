from flask import Flask, request, send_from_directory
import os
from werkzeug.utils import secure_filename
import pymysql

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads'
ALLOWED_EXTENSIONS = {'pdf'}

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def get_db_connection():
    connection = pymysql.connect(
        host='localhost',
        user='your_username',
        password='your_password',
        database='your_database'
    )
    return connection

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part'

    file = request.files['file']
    if file.filename == '':
        return 'No selected file'

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)

        connection = get_db_connection()
        try:
            with connection.cursor() as cursor:
                sql = "INSERT INTO pdf_files (filepath) VALUES (%s)"
                cursor.execute(sql, (filepath,))
            connection.commit()
        finally:
            connection.close()

        return 'File uploaded successfully', 200

@app.route('/download_pdf/<filename>', methods=['GET'])
def download_pdf(filename):
    filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
    if not os.path.isfile(filepath):
        return 'File not found', 404
    return send_from_directory(directory=app.config['UPLOAD_FOLDER'], path=filename, as_attachment=True)

if __name__ == '__main__':
    app.run(debug=True)


Make sure to replace `'your_username'`, `'your_password'`, and `'your_database'` with your actual MySQL database credentials. Also, ensure that the `uploads` directory exists in the same directory where this script is run.