from flask import Flask, request, redirect, url_for
import os
app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        f = request.files['file']
        path = os.path.join('uploads', f.filename)
        f.save(path)
        return redirect(url_for('index'))
    return '''<html><body>
                 <form action="" method="post" enctype="multipart/form-data">
                   <p><input type=file name=file>
                     <input type=submit value=Upload>
                 </form></body></html>'''
if __name__ == '__main__':
    app.run(debug=True)