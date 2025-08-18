from jinja2 import Environment, FileSystemLoader
from flask import Flask, request, make_response

app = Flask(__name__)
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get_template('index.html')
    rendered_template = template.render(name=name)
    return make_response(rendered_template)

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)