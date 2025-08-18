from flask import Flask, request
import subprocess

app = Flask(__name__)

def url_to_ping(f):
    def wrapper():
        url = request.args.get('url')
        if not url:
            return "URL parameter is missing"
        try:
            output = subprocess.check_output(['ping', '-c', '4', url])
            return output.decode()
        except Exception as e:
            return str(e)
    wrapper.__name__ = f.__name__
    return wrapper

@app.route('/ping')
@url_to_ping
def ping():
    pass

if __name__ == '__main__':
    app.run(debug=True)