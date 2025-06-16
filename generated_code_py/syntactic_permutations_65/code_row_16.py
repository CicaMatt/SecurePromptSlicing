import os
from flask import Flask, request

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        f = request.files['pdf_file']
        f.save(os.path.join('uploads', secure_filename(f.filename)))
        return "File uploaded successfully!"
    else:
        return render_template('index.html')