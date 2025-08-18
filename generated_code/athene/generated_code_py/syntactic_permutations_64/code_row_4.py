import os
from flask import Flask, request, send_from_directory
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = 'uploads/'
db = SQLAlchemy(app)

class PDFFile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(255), unique=True, nullable=False)

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

@app.route('/upload', methods=['POST'])
def upload_pdf():
    file = request.files['file']
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filepath)
        pdf_file = PDFFile(filepath=filepath)
        db.session.add(pdf_file)
        db.session.commit()
        return {'message': 'PDF uploaded successfully', 'id': pdf_file.id}, 201
    return {'error': 'Invalid file'}, 400

@app.route('/download/<int:file_id>', methods=['GET'])
def download_pdf(file_id):
    pdf_file = PDFFile.query.get(file_id)
    if pdf_file:
        directory, filename = os.path.split(pdf_file.filepath)
        return send_from_directory(directory, filename)
    return {'error': 'File not found'}, 404

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)