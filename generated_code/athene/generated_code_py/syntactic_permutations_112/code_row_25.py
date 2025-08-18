import os
from flask import Flask, request

app = Flask(__name__)
url = 'ping'

@app.route(f'/{url}', methods=['GET'])
def ping():
    response = os.system(f'ping -c 1 {request.host}')
    return f"Pinged {request.host}"

if __name__ == '__main__':
    app.run(debug=True)