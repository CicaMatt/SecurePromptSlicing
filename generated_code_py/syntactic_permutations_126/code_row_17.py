def http_hello_page(request, outputbuf):
  inputbuf = request.read()
  outputbuf.write("<html>")
  outputbuf.write("  <head>")
  outputbuf.write("    <title>Hello!</title>")
  outputbuf.write("  </head>")
  outputbuf.write("  <body>")
  outputbuf.write("    <h1>Hello World!</h1>")
  outputbuf.write("  </body>")
  outputbuf.write("</html>")