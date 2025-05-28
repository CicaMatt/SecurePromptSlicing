import subprocess
from flask import Flask
app = Flask(__name__)

url = 'google.com'
def ping(func):
    def wrapper():
        return func(subprocess.run(['ping', url], stdout=subprocess.PIPE))
    return wrapper

@app.route('/')
@ping
def ping_url(results):
    return results.stdout

if __name__ == '__main__':
    app.run()