from flask import Flask, request, redirect, url_for
import os
app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def upload():
    if request.method == 'POST':
        f = request.files['file']
        f.save(os.path.join(app.config['UPLOAD_FOLDER'], f.filename))
        return redirect(url_for('upload'))
    return '''
<!doctype html>
<title>Upload new File</title>
<h1>Upload new File</h1>
<form action="" method=post enctype=multipart/form-data>
  <p><input type=file name=file>
     <input type=submit value=Upload>
</form>
'''
if __name__ == '__main__':
    app.run()