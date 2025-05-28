import http.server as http_server

def http_hello_page(request):
    content_type = "text/html; charset=utf-8"
    response = bytes("<html>Hello, {}!</html>", encoding="utf-8")
    request.send_response(200)
    request.send_header("Content-Type", content_type)
    request.end_headers()
    request.wfile.write(response)