from flask import Flask, request, send_file
import os
app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS
@app.route('/upload', methods=['GET','POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['file']
        filename = file.filename
        if filename != '':
            filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(filepath)
            return send_file(filepath, as_attachment=True)
    return render_template("upload.html")