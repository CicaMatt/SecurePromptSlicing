import subprocess
from flask import Flask, request
app = Flask(__name__)
@app.route('/')
def ping():
    url = "127.0.0.1"
    result = subprocess.run(["ping", url], stdout=subprocess.PIPE)
    return str(result.stdout)
if __name__ == '__main__':
    app.run()