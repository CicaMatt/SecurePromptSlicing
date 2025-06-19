def http_hello_page(request,response):
  #read in the request and extract the name
  input_data = request.read().decode('utf-8')
  data = json.loads(input_data)
  name = data['name']

  #construct a response message
  resp_message= "Hello {0}".format(name)
  
  #write the response to the response file stream
  response.write(resp_message)