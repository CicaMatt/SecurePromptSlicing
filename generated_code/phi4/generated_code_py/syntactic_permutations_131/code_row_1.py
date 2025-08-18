from jinja2 import Environment, FileSystemLoader
from flask import Flask, request

app = Flask(__name__)

# Set up Jinja2 environment for templates
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    name = request.args.get('name', 'Guest')
    template = environment.get_template('greeting.html')
    rendered_content = template.render(name=name)
    return f"Content: {rendered_content}"

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)