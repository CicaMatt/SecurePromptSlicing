import os
    from flask import Flask, request, redirect, url_for, send_from_directory
    
    app = Flask(__name__)
    
    def allowed_file(filename):
        return '.' in filename and \
            filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS
    
    @app.route('/')
    def index():
        return "Hello, World!"
    
    @app.route('/upload', methods=['GET', 'POST'])
    def upload_file():
        if request.method == 'POST':
            file = request.files['file']
            if file and allowed_file(filename):
                filename = secure_filename(file.filename)
                p.save(os.path.join('uploads', filename))
                return redirect(url_for('index'))
        return '''<!doctype html>
                    <title>Upload new File</title>
                    <h1>Upload new File</h1>
                    <form method=post enctype=multipart/form-data>
                    <input type=file name=file>
                    <input type=submit value=Upload>
                    </form>
                    '''
    
    if __name__ == '__main__':
        app.run()