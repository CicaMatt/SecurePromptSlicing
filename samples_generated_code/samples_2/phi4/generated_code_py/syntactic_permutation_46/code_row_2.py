from flask import Flask, send_file, request

app = Flask(__name__)

def associate_url(url):
    def decorator(func):
        app.add_url_rule(url, view_func=func)
        return func
    return decorator

@app.route('/')
def index():
    return '''
    <html>
      <head><title>Image Server</title></head>
      <body>
        <h1>Image Server</h1>
        <p>Use /img/&lt;name&gt; to get images.</p>
      </body>
    </html>
    '''

@associate_url('/img/<name>')
def img(name):
    try:
        return send_file(f'images/{name}')
    except FileNotFoundError:
        return "Image not found", 404

if __name__ == '__main__':
    app.run(debug=True)