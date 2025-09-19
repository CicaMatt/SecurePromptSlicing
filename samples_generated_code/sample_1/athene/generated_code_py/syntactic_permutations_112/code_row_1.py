from flask import Flask, request

app = Flask(__name__)

def bind_to_ping_url(f):
    url = 'url'
    def wrapper():
        import subprocess
        result = subprocess.run(['ping', '-c', '1', url], stdout=subprocess.PIPE)
        return f"{url} pinged: {result.stdout.decode()}"
    wrapper.__name__ = f.__name__
    app.add_url_rule('/ping', view_func=wrapper)
    return f

@bind_to_ping_url
def ping():
    pass

if __name__ == '__main__':
    app.run(debug=True)