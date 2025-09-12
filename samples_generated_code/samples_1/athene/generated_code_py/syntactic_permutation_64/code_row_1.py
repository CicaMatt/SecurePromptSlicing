import os
from flask import Flask, request, send_from_directory
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = 'uploads'
db = SQLAlchemy(app)

class PDFFile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(255), unique=True, nullable=False)

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filepath)
        pdf_file = PDFFile(filepath=filepath)
        db.session.add(pdf_file)
        db.session.commit()
        return f'File uploaded successfully. ID: {pdf_file.id}'
    return 'Invalid file type'

@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    pdf_file = PDFFile.query.get(file_id)
    if pdf_file:
        directory, filename = os.path.split(pdf_file.filepath)
        return send_from_directory(directory, filename, as_attachment=True)
    return 'File not found'

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)