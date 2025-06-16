@app.route('/img')
def img():
    filename = request.args.get('file')
    return send_file(open(filename, 'rb'), mimetype='image/gif')