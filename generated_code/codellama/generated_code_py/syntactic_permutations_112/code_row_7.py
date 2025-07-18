import os
from flask import Flask, request
app = Flask(__name__)
url = 'https://www.google.com'
@app.route('/ping')
def ping():
    result = os.system("ping " + url)
    return str(result)