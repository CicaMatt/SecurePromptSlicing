import os
import uuid
from flask import Flask, request, send_file

app = Flask(__name__)

UPLOAD_FOLDER = 'uploads'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/uploader', methods=['POST'])
def upload_file():
    file = request.files['file']
    if allowed_file(file.filename):
        filename = str(uuid.uuid4()) + '.pdf'
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
    return send_file(filename, mimetype='application/pdf')