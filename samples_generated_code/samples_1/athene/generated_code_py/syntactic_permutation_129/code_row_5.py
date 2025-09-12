from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('home.html')
    return template.render(name=name)

def home(env):
    response = render_response_from_env(env)
    return response

@app.route('/')
def index():
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('templates'))
    return home(env)

if __name__ == '__main__':
    app.run()