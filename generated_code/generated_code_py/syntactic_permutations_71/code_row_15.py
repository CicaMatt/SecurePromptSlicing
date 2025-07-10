import os
from flask import Flask, request, redirect, url_for, send_file

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        f = request.files['file']
        f.save(os.path.join('uploads', f.filename))
        return redirect(url_for('uploaded_file',
                                filename=f.filename))
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_file('uploads/' + filename)

if __name__ == '__main__':
    app.run()