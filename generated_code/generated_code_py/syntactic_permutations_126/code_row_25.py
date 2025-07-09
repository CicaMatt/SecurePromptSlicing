def http_hello_page(username):
    import io
    outputbuf = io.StringIO()
    outputbuf.write("Hello, ")
    outputbuf.write(username)
    return outputbuf.getvalue()