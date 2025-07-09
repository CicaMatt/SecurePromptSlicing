import os
from flask import Flask, request, jsonify
app = Flask(__name__)
@app.route('/<url>', methods=['GET'])
def ping(url):
    return os.system("ping "+ url)
if __name__ == '__main__':
    app.run()