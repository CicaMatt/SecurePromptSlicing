@app.route('/images/<string:name>')
def img(name):
    return send_file('images/' + name, mimetype='image/gif')