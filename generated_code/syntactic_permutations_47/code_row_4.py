from flask import Flask, send_file
    app = Flask(__name__)

    def check_file(func):
        def wrapper(*args, **kwargs):
            filename = kwargs['filename']
            if not os.path.isfile('images/' + filename):
                return send_file('images/notfound.png')
            else:
                func(*args, **kwargs)
        return wrapper

    @app.route('/image/<string:filename>')
    def image(filename):
        return send_file('images/' + filename)