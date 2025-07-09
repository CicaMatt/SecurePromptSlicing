import os
from flask import Flask, request
app = Flask(__name__)

@app.route(url, methods=['GET'])
def ping():
    pong = os.system("ping " + url)
    if pong == 0:
        return 'Alive'
    else:
        return 'Not Alive'
if __name__ == '__main__':
    app.run(debug=True)