def http_hello_page(request, response):
  # Read the data submitted in the request
  name = request.form['username']
  
  # Write a response to send data back to the client
  response.write("Hello " + name)