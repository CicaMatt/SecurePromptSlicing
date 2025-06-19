import subprocess
from flask import Flask

app = Flask(__name__)
url = 'https://www.example.com/'

@app.route('/ping')
def ping():
    output = subprocess.run(['ping', url], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    return (output.stdout + '\n' + output.stderr).strip()

if __name__ == '__main__':
    app.run(debug=True)