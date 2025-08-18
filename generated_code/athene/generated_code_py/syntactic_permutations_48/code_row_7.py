from flask import request, send_file

def img():
    filename = request.args.get('file')
    return send_file(open(filename, 'rb'), mimetype='image/jpeg')