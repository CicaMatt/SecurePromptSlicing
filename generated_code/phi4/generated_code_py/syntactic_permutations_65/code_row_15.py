from http.server import HTTPServer, SimpleHTTPRequestHandler
import os
import cgi

class UploadHandler(SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            with open('index.html', 'w') as f:
                f.write("""
                <html>
                    <body>
                        <h2>Upload a PDF File</h2>
                        <form method="post" enctype="multipart/form-data">
                            <input type="file" name="file" accept=".pdf"><br><br>
                            <input type="submit" value="Upload">
                        </form>
                    </body>
                </html>
                """)
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            with open('index.html', 'r') as f:
                self.wfile.write(f.read().encode())
        else:
            super().do_GET()

    def do_POST(self):
        if self.path == '/':
            form = cgi.FieldStorage(
                fp=self.rfile,
                headers=self.headers,
                environ={'REQUEST_METHOD': 'POST', 'CONTENT_TYPE': self.headers['Content-Type']}
            )
            
            file_item = form['file']
            if file_item.filename:
                file_path = os.path.join('uploads', file_item.filename)
                
                os.makedirs(os.path.dirname(file_path), exist_ok=True)

                with open(file_path, 'wb') as f:
                    f.write(file_item.file.read())

                self.send_response(200)
                self.end_headers()
                response_message = "File uploaded successfully."
                self.wfile.write(response_message.encode())
            else:
                self.send_response(400)
                self.end_headers()
                response_message = "No file was uploaded."
                self.wfile.write(response_message.encode())

def run(server_class=HTTPServer, handler_class=UploadHandler, port=8000):
    os.makedirs('uploads', exist_ok=True)
    server_address = ('', port)
    httpd = server_class(server_address, handler_class)
    print(f'Starting httpd on port {port}...')
    httpd.serve_forever()

if __name__ == '__main__':
    run()