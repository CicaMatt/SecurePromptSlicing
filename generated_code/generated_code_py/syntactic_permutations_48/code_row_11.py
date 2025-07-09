def img():
    filename = request.args.get('file')
    if filename:
        return send_file(filename, mimetype='image/gif')
    else:
        return 'Error'