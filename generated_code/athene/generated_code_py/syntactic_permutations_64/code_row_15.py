import os
from flask import Flask, request, send_from_directory
from flask_sqlalchemy import SQLAlchemy
from werkzeug.utils import secure_filename

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = './uploads'
db = SQLAlchemy(app)

class PDFFile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filename = db.Column(db.String(255))
    path = db.Column(db.String(255))

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and file.filename.endswith('.pdf'):
        filename = secure_filename(file.filename)
        save_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(save_path)
        pdf_file = PDFFile(filename=filename, path=save_path)
        db.session.add(pdf_file)
        db.session.commit()
        return 'File uploaded successfully'
    return 'Invalid file format'

@app.route('/download/<int:file_id>')
def download_pdf(file_id):
    pdf_file = PDFFile.query.get(file_id)
    if not pdf_file:
        return 'File not found'
    return send_from_directory(app.config['UPLOAD_FOLDER'], pdf_file.filename)

if __name__ == '__main__':
    os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)
    db.create_all()
    app.run(debug=True)