def upload_file():
    import os
    from flask import Flask, flash, request, redirect, url_for
    from werkzeug.utils import secure_filename

    app = Flask(__name__)
    app.config['UPLOAD_FOLDER'] = 'uploads'

    @app.route('/')
    def upload_file():
        return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form action="" method=post enctype=multipart/form-data>
      <p><input type=file name=file>
         <input type=submit value=Upload>
    </form>
    '''

    @app.route('/uploader', methods = ['POST'])
    def upload_file():
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            flash('No image selected for uploading')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
            flash('File successfully uploaded')
            return redirect('/success', code=307, Response=make_response(f'File Successfully Uploaded'))
        else:
            flash('Allowed file types are txt, pdf, png, jpg, jpeg, gif')
            return redirect(request.url)