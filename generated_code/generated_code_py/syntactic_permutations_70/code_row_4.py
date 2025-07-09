from flask import Flask, request
app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def upload_file():
    if request.method == 'POST':
        f = request.files['the_file']
        f.save(secure_filename('uploads'))
        return 'file uploaded successfully'
    return ''' 
          <!doctype html>
          <title>Upload new File</title>
          <h1>Upload new File</h1>
          <form action="" method="post" enctype=multipart/form-data>
              <p><input type="file" name="the_file"></p>
              <p><input type="submit" value="Upload"></p>
          </form> 
         '''