import os
from flask import Flask, request, send_from_directory
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+pymysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = 'uploads/'
db = SQLAlchemy(app)

class PDFFile(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filename = db.Column(db.String(255))
    filepath = db.Column(db.String(255))

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

@app.route('/upload', methods=['POST'])
def upload_pdf():
    file = request.files['file']
    if file and file.filename.endswith('.pdf'):
        filename = file.filename
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        
        new_file = PDFFile(filename=filename, filepath=filepath)
        db.session.add(new_file)
        db.session.commit()
        
        return {'message': 'PDF uploaded successfully', 'id': new_file.id}
    else:
        return {'error': 'Invalid file'}, 400

@app.route('/download/<int:file_id>')
def download_pdf(file_id):
    file = PDFFile.query.get(file_id)
    if file:
        return send_from_directory(app.config['UPLOAD_FOLDER'], file.filename, as_attachment=True)
    else:
        return {'error': 'File not found'}, 404

if __name__ == '__main__':
    db.create_all()
    app.run(debug=True)