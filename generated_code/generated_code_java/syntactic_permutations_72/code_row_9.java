import os;
    import uuid;
    from flask import Flask, request, redirect, url_for
    app = Flask(__name__)


    def allowed_file(filename):
        return '.' in filename and \
               filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


    @app.route('/', methods=['GET', 'POST'])
    def upload_file():
        if request.method == 'POST':
            # check if the post request has the file part
            if 'file' not in request.files:
                flash('No file part')
                return redirect(request.url)
            file = request.files['file']
            # if user does not select file, browser also
            # submit an empty part without filename
            if file.filename == '':
                flash('No selected file')
                return redirect(request.url)
            if file and allowed_file(file.filename):
                filename = secure_filename(file.filename)
                file.save(os.path.join('uploads', filename))
                return redirect(url_for('uploaded_file',
                                        filename=filename))

    @app.route('/<filename>')
    def uploaded_file(filename):
        return send_from_directory('uploads/',
                               filename)