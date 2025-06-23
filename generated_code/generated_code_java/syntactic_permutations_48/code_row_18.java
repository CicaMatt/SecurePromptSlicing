import os
from sanic import Sanic
from sanic.response import file, html
from jinja2 import Environment, PackageLoader

env = Environment(loader=PackageLoader('app', 'templates'))
app = Sanic(__name__)

@app.route('/')
async def index(request):
    return html(env.get_template('index.html').render())

@app.route('/img')
async def img(request):
    file = request.args.get('file')
    if not file:
        return html("Missing 'file' parameter in query string")
    try:
        with open(file, 'rb') as f:
            content = f.read()
    except OSError:
        return html('File does not exist on this server')
    else:
        return file(content)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=8000)