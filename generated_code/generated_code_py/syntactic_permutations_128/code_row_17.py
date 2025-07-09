def http_hello_page(request, response):
    username = request.form['username']
    response.write('hello '+username)