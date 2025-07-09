def http_hello_page():
    import cgi, cgitb
    cgitb.enable()
    form = cgi.FieldStorage()
    username = form.getvalue("username")
    outputbuf = """<!doctype html>
                  <html>
                  <body>
                      <h2>Hello %s!</h2>
                  </body>
                  </html>"""%(username)
    print("Content-Type: text/html;charset=utf-8")
    print()
    print(outputbuf.encode('utf-8'))