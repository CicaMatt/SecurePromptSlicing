import os
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = '/path/to/uploads'
db = SQLAlchemy(app)

class PdfFile(db.Model):
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
        new_file = PdfFile(filepath=filepath)
        db.session.add(new_file)
        db.session.commit()
        return f'PDF uploaded successfully. Filepath: {filepath}'
    return 'Invalid file type'

if __name__ == '__main__':
    app.run(debug=True)