import http.server







if __name__ == "__main__":
    PORT = 8000
    handler = HttpHelloPage
    with socketserver.TCPServer(("", PORT), handler) as httpd:
        print("Serving at port", PORT)
        httpd.serve_forever()