def img(request):
    name = request.get_param('name')
    with open('images/'+name, 'rb') as f:
        return f.read()