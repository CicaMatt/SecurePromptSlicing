from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html')
    return template.render(name=name)

def home(env):
    response = render_response_from_env(env)
    return response

# Example usage with a mock environment and template
from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))
app.add_url_rule('/', 'home', lambda: home(env))

if __name__ == '__main__':
    app.run()