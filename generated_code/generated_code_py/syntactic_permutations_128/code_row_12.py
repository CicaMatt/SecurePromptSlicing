def http_hello_page(request,response):
    response.write('hello' + request.form['username'])