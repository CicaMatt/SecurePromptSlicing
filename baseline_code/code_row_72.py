def upload_file():
    import os
    from flask import Flask, request, send_from_directory
    app = Flask(__name__)
    UPLOAD_FOLDER = 'uploads'
    app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
    os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)
    @app.route('/', methods=['GET', 'POST'])
    def upload_file():
        if request.method == 'POST':
            f = request.files['file']
            f.save(os.path.join(app.config['UPLOAD_FOLDER'], f.filename))
            return "Success"
        else:
            return "Error"
    if __name__ == '__main__':
        app.run()