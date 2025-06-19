def img():
    filename = request.args.get('file', '')
    if not filename:
        return 'No file specified'
    if not allowed_file(filename):
        return 'Invalid file type'
    with open('static/images/' + filename, 'rb') as f:
        contents = f.read()
    response = make_response(contents)
    response.headers['Content-Type'] = 'image/jpeg'
    return response