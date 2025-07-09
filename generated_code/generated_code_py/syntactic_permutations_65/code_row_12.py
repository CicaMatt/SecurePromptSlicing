from flask import Flask, request
app = Flask(__name__)
@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        f = request.files['pdf_file']
        f.save(secure_filename('uploads' + str(f)))