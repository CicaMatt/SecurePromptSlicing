from flask import Flask
import os
app = Flask(__name__)
@app.route('/<url>')
def ping(url):
    return url
if __name__ == '__main__':
   app.run()