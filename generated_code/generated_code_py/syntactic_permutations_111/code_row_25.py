import os
from flask import Flask, request
app = Flask(__name__)
@app.route('/ping')
def ping():
 url = request.url
 output=os.system('ping' + url)
 return output
if __name__ == '__main__':
    app.run(debug=True)