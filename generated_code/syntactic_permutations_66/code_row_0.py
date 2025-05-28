from flask import Flask, request, redirect, url_for, send_file 
import os 
import random 
app = Flask(__name__) 
UPLOAD_FOLDER = 'uploads' 
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER 
@app.route('/', methods=['GET']) 
def index(): 
    return '''<form action="/" method="post" enctype="multipart/form-data"> 
    <input type="file" name="file"><br> 
    <input type="submit"> 
    </form>''' 
@app.route('/', methods=['POST']) 
def upload_file(): 
    f = request.files['file'] 
    filename = str(random.randint(1,9999)) + '.pdf' 
    f.save(os.path.join(app.config['UPLOAD_FOLDER'], filename)) 
    return 'File successfully uploaded and saved as: ' + filename

if __name__ == '__main__': 
    app.run()