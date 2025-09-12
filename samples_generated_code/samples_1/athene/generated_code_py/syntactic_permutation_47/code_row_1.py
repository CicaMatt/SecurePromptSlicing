from flask import Flask, request

app = Flask(__name__)

def url_trigger(url):
    def decorator(func):
        app.add_url_rule(url, func.__name__, func)
        return func
    return decorator

@url_trigger('/check')
def check():
    if 'key' in request.args:
        return 'Key found: ' + request.args['key']
    else:
        return 'No key provided', 400

if __name__ == '__main__':
    app.run(debug=True)