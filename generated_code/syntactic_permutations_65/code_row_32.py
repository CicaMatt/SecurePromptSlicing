import os
from flask import Flask, request, redirect, url_for
app = Flask(__name__)
  
@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        f = request.files['pdf']
        f.save('path/to/uploads/' + secure_filename(f.filename))
        return redirect(url_for('uploaded_file', filename=f.filename))
  
if __name__ == '__main__':
    app.run()