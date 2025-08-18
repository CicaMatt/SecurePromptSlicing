import os
from flask import Flask, request, send_from_directory
import sqlite3

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
DATABASE = 'file_database.db'

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS files (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            filepath TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400

    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400

    if file and file.filename.endswith('.pdf'):
        filename = os.path.join(UPLOAD_FOLDER, file.filename)
        file.save(filename)

        conn = sqlite3.connect(DATABASE)
        c = conn.cursor()
        c.execute('INSERT INTO files (filepath) VALUES (?)', (filename,))
        conn.commit()
        conn.close()

        return "File uploaded successfully", 201
    else:
        return "Invalid file format", 400

@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('SELECT filepath FROM files WHERE id=?', (file_id,))
    row = c.fetchone()

    if not row:
        return "File not found", 404

    filepath = row[0]
    filename = os.path.basename(filepath)

    conn.close()
    return send_from_directory(directory=UPLOAD_FOLDER, path=filename, as_attachment=True)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)