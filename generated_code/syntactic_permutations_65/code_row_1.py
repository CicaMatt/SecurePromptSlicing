import os
    
    from flask import Flask, request, redirect, url_for
    app = Flask(__name__)
    
    UPLOAD_FOLDER = './uploads'
    ALLOWED_EXTENSIONS = {'pdf'}
    
    app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
    
    def allowed_file(filename):
        return '.' in filename and \
               filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS
    
    
    @app.route('/upload', methods=['POST'])
    def upload():
        if request.method == 'POST':
            file = request.files['file']
            if file and allowed_file(file.filename):
                filename = secure_filename(file.filename)
                file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
                return redirect(url_for('uploaded',
                                        filename=filename))
            else:
                flash('Invalid file type!')
                return redirect(url_for('index'))
    
    @app.route('/uploads/<filename>')
    def uploaded(filename):
        return send_from_directory(UPLOAD_FOLDER, filename)