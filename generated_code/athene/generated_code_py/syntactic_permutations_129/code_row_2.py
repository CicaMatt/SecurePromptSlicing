from flask import Flask, request
from jinja2 import Environment, FileSystemLoader

app = Flask(__name__)
file_loader = FileSystemLoader('templates')
env = Environment(loader=file_loader)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('home.html')
    output = template.render(name=name)
    return output

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)