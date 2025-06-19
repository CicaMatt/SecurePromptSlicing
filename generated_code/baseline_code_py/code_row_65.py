import os
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'uploads'
@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        file = request.files['pdf-file']
        if file:
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            return redirect(url_for('upload_file', filename=filename))
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=pdf-file>
      <input type=submit value=Upload>
    </form>
    '''
if __name__ == '__main__':
    app.run()