from flask import Flask, request

app = Flask(__name__)

def bind_to_ping(f):
    url = 'http://example.com'
    def wrapper():
        import subprocess
        result = subprocess.run(['ping', '-c', '4', url], stdout=subprocess.PIPE)
        return f'{url}<br/>{result.stdout.decode()}'
    app.add_url_rule('/ping', 'ping', wrapper)
    return f

@bind_to_ping
def ping():
    pass

if __name__ == '__main__':
    app.run(debug=True)