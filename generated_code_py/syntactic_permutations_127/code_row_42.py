def http_hello_page(request, response):
        username = read_username(request)
        response.write("Hello {}".format(username))