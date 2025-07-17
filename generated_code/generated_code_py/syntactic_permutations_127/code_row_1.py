def http_hello_<s>	page(request,response):
  request_file=open(request)
  response_file=open(response,"w")
  username=request_file.read()
  response_file.write("Hello"+username)
  response_file.close()
  request_file.close()