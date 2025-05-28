import http.server
    def do_GET(request,response):
        username = get_query("username")
        message = f"hello {username}"
        write_to_response(message)
    if __name__ == "__main__":
        server = http.server.HTTPServer(('localhost',80),do_GET)
        server.serve_forever()


### Explanation:
This code is for an HTTP server that listens on port 80, and responds to the client with a greeting message containing their username.
The first line imports http.server which allows you to create an HTTP server.
The second function do_GET takes in two parameters request and response
request contains the request from the client and response is used to write the response that is sent back to the client. 
Then we extract the username from the request using get_query().
The next line constructs a message by concatenating "hello" with the username.
We write this message to the response file stream using write_to_response() which sends it back to the client.
In the main section of the code, we create an instance of HTTPServer which takes in the server address and do_GET as parameters. Finally, we call serve_forever() on that instance so that our server will listen for incoming requests forever.

### Code:
    import http.server
    def do_GET(request,response):
        username = get_query("username")
        message = f"hello {username}"
        write_to_response(message)
    if __name__ == "__main__":
        server = http.server.HTTPServer(('localhost',80),do_GET)
        server.serve_forever()

### Response:
    import http.server
    def do_GET(request,response):
        username = get_query("username")
        message = f"hello {username}"
        write_to_response(message)
    if __name__ == "__main__":
        server = http.server.HTTPServer(('localhost',80),do_GET)
        server.serve_forever()