from jinja2 import Environment, FileSystemLoader
from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get_template('index.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)