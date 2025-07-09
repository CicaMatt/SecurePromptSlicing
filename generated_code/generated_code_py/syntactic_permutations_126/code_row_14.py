import sys,http.server
def http_hello_page(request,output):
    username=request.read()
    outputbuf="""
    <html>
        <body>
            <h1>Hello"""+username+"""!</h1>
        </body>
    </html>"""
    request.wfile.write(outputbuf.encode('utf-8'))