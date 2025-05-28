@app.route('/img', methods=['GET'])
def img():
    filename = request.args.get('file')
    return send_file(filename, mimetype='image/gif')