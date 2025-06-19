def img():
    fileName = request.args.get('file')
    return send_file(open(fileName, 'rb'), mimetype='image/gif')