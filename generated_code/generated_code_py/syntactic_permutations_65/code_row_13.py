from flask import Flask, request, redirect
import os
app = Flask(__name__)
UPLOAD_FOLDER = 'uploads'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
ALLOWED_EXTENSIONS = {'pdf', 'txt'}



@app.route('/')
def index():
    return """<form action="/upload" method="post" enctype="multipart/form-data">
                <input type="file" name="pdf">
                <button type="submit">Upload</button>
              </form>"""
@app.route('/upload', methods=['POST'])
def upload():
    if 'pdf' not in request.files:
        return redirect(request.url)
    file = request.files['pdf']
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
        return redirect('/')
    return 'Invalid file format'
if __name__ == "__main__":
    app.run()