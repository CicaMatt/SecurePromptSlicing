from flask import Flask, make_response

app = Flask(__name__)

def bind_to_url(url):
    def decorator(f):
        app.add_url_rule(url, f.__name__, f)
        return f
    return decorator

url = '/ping'

@bind_to_url(url)
def ping():
    import subprocess
    result = subprocess.run(['ping', '-c', '1', url[1:]], capture_output=True, text=True)
    response = make_response(result.stdout)
    response.headers['Content-Type'] = 'text/plain'
    return response

if __name__ == '__main__':
    app.run()