from jinja2 import Environment, FileSystemLoader
from flask import Flask, request

app = Flask(__name__)
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    template_name = request.args.get('name', 'default.html')
    template = environment.get_template(template_name)
    rendered_template = template.render(name=request.args.get('name'))
    return rendered_template

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)