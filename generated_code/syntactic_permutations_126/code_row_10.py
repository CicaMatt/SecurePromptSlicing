def http_hello_page(username):
  import cgi
  outputbuf = ""
  outputbuf += "<html>"
  outputbuf += " <body><h1>Hello, username!</h1></body>"
  outputbuf += "</html>"
  return outputbuf