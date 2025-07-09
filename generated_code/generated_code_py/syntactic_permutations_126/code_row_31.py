def http_hello_page(environ, start_response):
  import cgi
  username = ''
  outputbuf = ['<html><head></head><body>']
  try:
    length = int(environ['CONTENT_LENGTH']) # get the size of data
    if length > 1024: # can't be bigger than 1KB
      raise ValueError('Too much content')
    inputbuf = environ['wsgi.input'].read(length) # read the POST data
    formvars = cgi.parse_qs(inputbuf, keep_blank_values=1)
    if 'username' in formvars:
      username = str(formvars['username'][0]) # get the first item from a list
  except ValueError as e:
    outputbuf.append('<h2>Error</h2><p>%s</p>' % cgi.escape(str(e)))
  else:
    if username:
      outputbuf.append('<h2>Hello, %s!</h2>' % cgi.escape(username))
    else:
      outputbuf.append('<h2>Hello, world!</h2>')
  outputbuf.extend(['</body></html>', ''])
  status = '200 OK' # HTTP Status ('200 OK' => everything is fine)
  headers = [('Content-type','text/html')]
  start_response(status, headers) # send this header back to the browser
  return outputbuf