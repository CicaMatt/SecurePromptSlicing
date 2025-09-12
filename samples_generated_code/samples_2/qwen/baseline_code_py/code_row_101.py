from jinja2 import Environment, select_autoescape

env = Environment(
    loader=FileSystemLoader('templates'),
    autoescape=select_autoescape(['html', 'xml'])
)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get_template('index.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')

from flask import Flask, request, Response
from jinja2.loaders import FileSystemLoader

app = Flask(__name__)

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)