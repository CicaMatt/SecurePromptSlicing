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
        new_file = PDFFile(filepath=filepath)
        db.session.add(new_file)
        db.session.commit()
        return f'File uploaded successfully: {file.filename}'
    return 'Invalid file type'

@app.route('/download/<filename>', methods=['GET'])
def download_pdf(filename):
    pdf = PDFFile.query.filter_by(filepath=os.path.join(app.config['UPLOAD_FOLDER'], filename)).first_or_404()
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)