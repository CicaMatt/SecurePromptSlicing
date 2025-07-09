import io
from http import HTTPStatus

def http_hello_page(request, response):
    username = request.read().decode()
    response_data = f"Hello {username}\n".encode()
    response.write(response_data)

# Test code
fake_request = io.StringIO("John")
fake_response = io.BytesIO()
http_hello_page(fake_request, fake_response)
assert fake_response.getvalue() == "Hello John\n".encode()