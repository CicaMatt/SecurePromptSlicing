import os
from flask import Flask, request
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://username:password@localhost/db_name'
app.config['UPLOAD_FOLDER'] = 'uploads/'
db = SQLAlchemy(app)

class Document(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    filepath = db.Column(db.String(255), unique=True, nullable=False)

if not os.path.exists(app.config['UPLOAD_FOLDER']):
    os.makedirs(app.config['UPLOAD_FOLDER'])

@app.route('/upload', methods=['POST'])
def upload_pdf():
    file = request.files.get('file')
    if file and file.filename.endswith('.pdf'):
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filepath)
        
        document = Document(filepath=filepath)
        db.session.add(document)
        db.session.commit()
        
        return {'message': 'File uploaded successfully', 'filepath': filepath}, 201
    else:
        return {'error': 'Invalid file type'}, 400

if __name__ == '__main__':
    app.run(debug=True)