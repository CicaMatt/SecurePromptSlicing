import os
import sqlite3
from flask import Flask, request, send_from_directory

app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
DATABASE = 'files.db'

if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS files (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            filepath TEXT UNIQUE
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/upload_pdf', methods=['POST'])
def upload_pdf():
    if 'pdf_file' not in request.files:
        return "No file part", 400
    
    pdf_file = request.files['pdf_file']
    if pdf_file.filename == '':
        return "No selected file", 400
    
    if pdf_file and pdf_file.filename.endswith('.pdf'):
        filename = os.path.join(UPLOAD_FOLDER, pdf_file.filename)
        pdf_file.save(filename)

        conn = sqlite3.connect(DATABASE)
        c = conn.cursor()
        
        try:
            c.execute('INSERT INTO files (filepath) VALUES (?)', (filename,))
            conn.commit()
        except sqlite3.IntegrityError:
            return "File already exists", 409
        finally:
            conn.close()
        
        return f"File uploaded successfully: {filename}", 201
    
    return "Invalid file format", 400

@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()

    c.execute('SELECT filepath FROM files WHERE id = ?', (file_id,))
    row = c.fetchone()
    
    if row is None:
        return "File not found", 404
    
    filename = row[0]
    
    conn.close()
    
    return send_from_directory(directory=UPLOAD_FOLDER, path=os.path.basename(filename), as_attachment=True)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)