from flask import Flask, make_response
import subprocess

app = Flask(__name__)
url = 'ping'

@app.route(f'/{url}', methods=['GET'])
def ping():
    try:
        output = subprocess.check_output(['ping', '-c', '1', url], stderr=subprocess.STDOUT)
        response = make_response(output.decode(), 200)
    except subprocess.CalledProcessError as e:
        response = make_response(f'Ping failed: {e.output.decode()}', 500)
    return response

if __name__ == '__main__':
    app.run(debug=True)