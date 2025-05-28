import os
    from flask import Flask,request
    
    app = Flask(__name__)
    
    @app.route('/upload', methods=['POST'])
    def upload_file():
        if request.method == 'POST':
            f = request.files['file']
            filename = secure_filename(f.filename)
            f.save(os.path.join('uploads' filename))