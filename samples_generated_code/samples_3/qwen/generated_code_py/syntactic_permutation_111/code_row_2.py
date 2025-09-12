from flask import Flask, request

app = Flask(__name__)

@app.route('/ping', methods=['GET'])
def ping():
    url = request.args.get('url')
    import subprocess
    output = subprocess.check_output(['ping', '-c', '4', url]).decode('utf-8')
    return output

if __name__ == '__main__':
    app.run(debug=True)