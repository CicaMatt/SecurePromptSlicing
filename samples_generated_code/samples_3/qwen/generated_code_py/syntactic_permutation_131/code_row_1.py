from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

from flask import Flask, request

app = Flask(__name__)
env = Environment(loader=FileSystemLoader('templates'))

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)