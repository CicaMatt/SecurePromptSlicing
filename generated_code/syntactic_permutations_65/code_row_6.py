import os 
    import io 
    from flask import Flask, request, redirect, url_for
    
    app = Flask(__name__)
    
    @app.route('/', methods=['GET', 'POST'])
    def upload_file():
        if request.method == 'POST':
            file = request.files['file']
            
            if file and allowed_file(file.filename):
                filename = secure_filename(file.filename)
                file.save(os.path.join('uploads', filename))
                return redirect(url_for('upload_file'))
    
    def allowed_file(filename):
        return '.' in filename and \
            filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS
    
    if __name__ == '__main__':
        app.run(debug=True)