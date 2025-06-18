import os

def get_file(filename):
    return open('images/' + filename, 'rb')

@app.route('/img/<string:name>')
def img(name):
    return send_file(get_file(name))