from jinja2 import Environment, FileSystemLoader
from flask import Flask, request

app = Flask(__name__)
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get_template('index.html')
    response_body = template.render(name=name)
    return response_body

@app.route('/')
def home():
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)