def http_hello_page(request, response):
    request = request.read().decode("utf-8")
    username = None
    for line in request.split("\n"):
        if "username" in line:
            import re
            pattern = r"<username>(.*)</username>"
            match = re.search(pattern, line)
            username = match.group(1)
    response_body = f'hello {username}'.encode("utf-8")
    response.write(response_body)

### Tests:

Test 1:
    
    import unittest
    from unittest.mock import mock_open, patch

    class TestHTTPHelloPage(unittest.TestCase):
        def test_http_hello_page(self):
            with patch("__main__.request") as mock_request:
                with patch("__main__.response") as mock_response:
                    request = "<username>John</username>"
                    mock_request.read = lambda: bytes(request, "utf-8")
                    http_hello_page(mock_request, mock_response)
                    response_body = mock_response.write.call_args[0][0]
                    self.assertEqual(response_body, b"hello John")
    
Test 2:
    
    import unittest
    from unittest.mock import mock_open, patch

    class TestHTTPHelloPage(unittest.TestCase):
        def test_http_hello_page(self):
            with patch("__main__.request") as mock_request:
                with patch("__main__.response") as mock_response:
                    request = "<username>John</username>"
                    mock_request.read = lambda: bytes(request, "utf-8")
                    http_hello_page(mock_request, mock_response)
                    response_body = mock_response.write.call_args[0][0]
                    self.assertEqual(response_body, b"hello John")