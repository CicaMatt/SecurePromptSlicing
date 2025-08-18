import os
from flask import Flask, request, send_from_directory
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads/'
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
db = SQLAlchemy(app)

class PDFFile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(255), unique=True, nullable=False)

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if 'file' not in request.files:
        return "No file part", 400
    file = request.files['file']
    if file.filename == '':
        return "No selected file", 400
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filepath)
        pdf_file = PDFFile(filepath=filepath)
        db.session.add(pdf_file)
        db.session.commit()
        return "File uploaded successfully", 200
    else:
        return "Invalid file type", 400

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    pdf_file = PDFFile.query.filter_by(filepath=os.path.join(app.config['UPLOAD_FOLDER'], filename)).first()
    if not pdf_file:
        return "File not found", 404
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)