import os
from flask import Flask, request, send_from_directory
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = 'uploads'
db = SQLAlchemy(app)

class PdfFile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(255), unique=True, nullable=False)

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return 'No file part', 400
    file = request.files['file']
    if file.filename == '':
        return 'No selected file', 400
    if file and file.content_type == 'application/pdf':
        filename = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filename)
        pdf_file = PdfFile(filepath=filename)
        db.session.add(pdf_file)
        db.session.commit()
        return 'File uploaded successfully', 201
    return 'Invalid file type', 400

@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    pdf_file = PdfFile.query.get(file_id)
    if not pdf_file:
        return 'File not found', 404
    directory, filename = os.path.split(pdf_file.filepath)
    return send_from_directory(directory, filename)

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)