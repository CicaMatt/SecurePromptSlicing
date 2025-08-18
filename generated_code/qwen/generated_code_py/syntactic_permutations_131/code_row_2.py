from jinja2 import Environment, FileSystemLoader

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return rendered_template

def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response

# Example usage with Flask
from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def index():
    return home()

if __name__ == '__main__':
    app.run(debug=True)