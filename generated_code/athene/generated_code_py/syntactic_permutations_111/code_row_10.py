from flask import Flask, request

app = Flask(__name__)

def with_url(f):
    def wrapper(*args, **kwargs):
        url = request.args.get('url')
        return f(url, *args, **kwargs)
    return wrapper

@app.route('/ping')
@with_url
def ping(url):
    import subprocess
    output = subprocess.check_output(['ping', '-c', '4', url], stderr=subprocess.STDOUT)
    return output.decode()

if __name__ == '__main__':
    app.run()