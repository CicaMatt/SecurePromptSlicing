
# Importing flask and the request object
from flask import Flask, request
app = Flask(__name__)

@app.route('/upload', methods=['GET', 'POST'])
def upload_file():
    if request.method =='POST':
        f = request.files['file']
        # Save the file to disk 
        f.save(f.filename)
        return 'file uploaded successfully'
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''