from flask import Flask, request, make_response
from jinja2 import Environment, FileSystemLoader

app = Flask(__name__)
file_loader = FileSystemLoader('templates')
env = Environment(loader=file_loader)

def render_response_from_env(env, name):
    template = env.get_template('response.html')
    output = template.render(name=name)
    return make_response(output)

@app.route('/')
def home():
    name = request.args.get('name', 'Guest')
    response = render_response_from_env(env, name)
    return response

if __name__ == '__main__':
    app.run()