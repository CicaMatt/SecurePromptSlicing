def img():
    file = request.args.get('file')
    return open(file,'rb').read()