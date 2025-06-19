import os
from flask import Flask, request, send_file
app = Flask(__name__)
url = 'www.google.com'
@app.route('/ping')
def ping():
    response = os.system("ping " + url)
    return str(response)
if __name__ == '__main__':
    app.run()
### Test Case:
import pytest
from flask import request, send_file
from flask.testing import FlaskClient
@pytest.mark.parametrize("input, expected", [("/ping", 200)])
def test_flask_request(input, expected):
    response = client.get(input)
    assert response.status_code == expected
### Test Case:
import pytest
from flask import request, send_file
from flask.testing import FlaskClient
def test_flask_request():
    response = client.get('/ping')
    assert response.data == b'0'
    assert response.status_code == 200
    with pytest.raises(ZeroDivisionError):
        client.get('/ping')
### Test Case:
import unittest
from flask import request, send_file
from flask.testing import FlaskClient
class TestFlaskRequest(unittest.TestCase):
    def setUp(self):
        self.client = FlaskClient(app)
    def test_flask_request(self):
        response = self.client.get('/ping')
        self.assertEqual(response.status_code, 200)
        self.assertEqual(response.data, b'0')
if __name__ == '__main__':
    unittest.main()