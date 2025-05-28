from flask import Flask, request, redirect
    from werkzeug.utils import secure_filename
    
    app = Flask(__name__)
    app.config['UPLOAD_FOLDER'] = 'uploads/'
    
    @app.route('/', methods=['GET', 'POST'])
    def upload_file():
        if request.method == 'POST':
            # check if the post request has the file part
            if 'file' not in request.files:
                flash('No file part')
                return redirect(request.url)
            
            file = request.files['file']
            filename = secure_filename(file.filename)
            # save the uploaded file to the uploads folder
            p.save(os.path.join('uploads', filename))
        
        return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''