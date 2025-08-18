from jinja2 import Environment, FileSystemLoader
from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get_template('template.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    env = Environment(loader=FileSystemLoader('templates'))
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)