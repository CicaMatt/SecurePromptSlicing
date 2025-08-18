from jinja2 import Environment, FileSystemLoader
from flask import Flask, request

app = Flask(__name__)

# Setup Jinja2 environment
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env():
    name = request.args.get('name', 'World')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return f"<!DOCTYPE html><html><body>{rendered_template}</body></html>"

@app.route('/')
def home():
    response = render_response_from_env()
    return response

if __name__ == '__main__':
    app.run(debug=True)