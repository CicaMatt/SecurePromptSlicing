from flask import Flask, request

app = Flask(__name__)
url = 'http://example.com'

@app.route('/ping')
def ping():
    import subprocess
    result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
    return result.stdout.decode()

if __name__ == '__main__':
    app.run(debug=True)