from jinja2 import Environment, FileSystemLoader
from flask import Flask, request

app = Flask(__name__)

env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    name = request.args.get('name', 'Guest')
    template = environment.get_template('hello.html')
    rendered_template = template.render(name=name)
    return f"Response: {rendered_template}"

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run()


Make sure you have a `templates` directory containing the `hello.html` file with Jinja2 templating syntax, for example:





You also need to install the required packages:


pip install Flask Jinja2