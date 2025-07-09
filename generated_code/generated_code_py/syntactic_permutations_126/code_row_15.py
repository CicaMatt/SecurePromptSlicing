def http_hello_page(req, res):
    username = req['username']
    outputbuf = "Hello, " + username + "!"
    res.write(outputbuf)
    res.close()