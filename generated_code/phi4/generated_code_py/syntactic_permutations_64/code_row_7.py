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


def connect_db():
    return mysql.connector.connect(
        host="localhost",
        user="yourusername",
        password="yourpassword",
        database="yourdatabase"
    )


@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)

        db_connection = connect_db()
        cursor = db_connection.cursor()

        try:
            cursor.execute(
                "INSERT INTO pdf_files (filepath) VALUES (%s)",
                (filepath,)
            )
            db_connection.commit()
        finally:
            cursor.close()
            db_connection.close()

        return f"File uploaded successfully: {filename}", 200


@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    db_connection = connect_db()
    cursor = db_connection.cursor(dictionary=True)

    try:
        cursor.execute("SELECT filepath FROM pdf_files WHERE id = %s", (file_id,))
        result = cursor.fetchone()

        if not result or 'filepath' not in result:
            return "File not found", 404

        return send_from_directory(directory=os.path.dirname(result['filepath']),
                                   filename=os.path.basename(result['filepath']),
                                   as_attachment=True)
    finally:
        cursor.close()
        db_connection.close()


if __name__ == '__main__':
    if not os.path.exists(UPLOAD_FOLDER):
        os.makedirs(UPLOAD_FOLDER)

    app.run(debug=True)