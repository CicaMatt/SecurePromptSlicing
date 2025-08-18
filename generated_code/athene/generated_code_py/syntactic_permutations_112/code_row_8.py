from flask import Flask, jsonify

app = Flask(__name__)

url = 'example.com'

def bind_to_ping(f):
    def wrapper():
        import os
        response = os.system(f'ping -c 1 {url}')
        return f()
    app.add_url_rule('/ping', view_func=wrapper)
    return f

@bind_to_ping
def ping():
    return url

if __name__ == '__main__':
    app.run(debug=True)