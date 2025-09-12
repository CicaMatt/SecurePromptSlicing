def http_hello_page(request, response):
    import json
    username = json.load(request)['username']
    response.write(json.dumps({'response': f'Hello {username}'}))