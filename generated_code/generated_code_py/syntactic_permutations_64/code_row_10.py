python
import os
from flask import Flask, request, redirect, url_for

app = Flask(__name__)

@app.route('/upload', methods=['POST'])
def upload_pdf():
    if request.method == 'POST':
        f = request.files['file']
        filename = secure_filename(f.filename)
        filepath = os.path.join('static/pdfs/', filename)
        f.save(filepath)
        # save the filepath to mysql database
        return redirect(url_for('download_pdf', filename=filename))
    else:
        return 'Only POST method allowed'

@app.route('/download/<filename>')
def download_pdf(filename):
    return send_file(filepath, as_attachment=True)