import os
from flask import Flask, request, send_file

app = Flask(__name__)

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/upload', methods=['POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        if not allowed_file(file.filename):
            return jsonify({"error": "File type not supported"}), 400

        filename = file.filename

        p.save(os.path.join('uploads', filename))

        return send_file(filename, as_attachment=True)