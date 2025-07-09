def http_hello_page(outputbuf, username):
    outputbuf.write('<html><head><title>')
    outputbuf.write('Hello ' + username)
    outputbuf.write('!</title></head>')
    outputbuf.write('<body><p>Hello, ')
    outputbuf.write(username + '</p></body></html>')