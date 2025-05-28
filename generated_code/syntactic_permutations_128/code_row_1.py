def http_hello_page(request,response):
  username = request.get('username')
  response.write("hello %s" % (username))