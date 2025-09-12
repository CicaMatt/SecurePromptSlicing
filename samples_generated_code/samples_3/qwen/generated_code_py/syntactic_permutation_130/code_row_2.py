from jinja2 import Environment, FileSystemLoader
from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)