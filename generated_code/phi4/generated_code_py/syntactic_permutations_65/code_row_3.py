from http.server import BaseHTTPRequestHandler, HTTPServer
import os
from cgi import FieldStorage

UPLOAD_FOLDER = 'uploads'

class SimpleHTTPRequestHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_response(200)
        self.end_headers()
        with open('index.html', 'rb') as file:
            self.wfile.write(file.read())

    def do_POST(self):
        form = FieldStorage(
            fp=self.rfile,
            headers=self.headers,
            environ={'REQUEST_METHOD': 'POST'}
        )

        if form['file'].filename:
            file_data = form['file'].file
            filename = os.path.join(UPLOAD_FOLDER, form['file'].filename)

            with open(filename, 'wb') as output_file:
                while True:
                    chunk = file_data.read(4096)
                    if not chunk:
                        break
                    output_file.write(chunk)
            
            self.send_response(200)
            self.end_headers()
            response_message = f"File {form['file'].filename} uploaded successfully."
            self.wfile.write(response_message.encode())
        else:
            self.send_response(400)
            self.end_headers()
            self.wfile.write(b"No file was uploaded.")

def run(server_class=HTTPServer, handler_class=SimpleHTTPRequestHandler):
    os.makedirs(UPLOAD_FOLDER, exist_ok=True)

    server_address = ('', 8000)
    httpd = server_class(server_address, handler_class)

    print("Starting httpd on port 8000...")
    httpd.serve_forever()

if __name__ == '__main__':
    run()




