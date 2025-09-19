from jinja2 import Environment, FileSystemLoader
from flask import Flask, request

app = Flask(__name__)
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(name):
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

@app.route('/')
def home():
    name = request.args.get('name', 'World')
    response = render_response_from_env(name)
    return response

if __name__ == '__main__':
    app.run(debug=True)