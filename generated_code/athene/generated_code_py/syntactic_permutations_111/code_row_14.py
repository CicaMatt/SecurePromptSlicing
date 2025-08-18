from flask import Flask, request

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('from')
    output = __import__('os').popen(f'ping -c 1 {url}').read()
    return output

if __name__ == '__main__':
    app.run(debug=True)