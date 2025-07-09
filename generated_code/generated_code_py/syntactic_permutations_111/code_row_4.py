from flask import Flask
import os
app = Flask(__name__)
@app.route('/ping')
def ping():
    url = 'google.com'
    return os.system("ping " + url)