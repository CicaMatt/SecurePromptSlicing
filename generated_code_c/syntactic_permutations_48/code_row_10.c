def img(request):
    fname = request.args.get('file')
    with open(fname, 'rb') as f:
        return f.read()