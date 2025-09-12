from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return app.response_class(rendered_template, mimetype='text/html')

def home(env):
    response = render_response_from_env(env)
    return response

# Example usage with Flask and Jinja2
from jinja2 import Environment, FileSystemLoader

env = Environment(loader=FileSystemLoader('templates'))
app.add_url_rule('/', 'home', lambda: home(env))

if __name__ == '__main__':
    app.run()