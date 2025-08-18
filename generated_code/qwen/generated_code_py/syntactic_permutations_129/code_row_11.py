from jinja2 import Environment, FileSystemLoader
from flask import Flask, Response

app = Flask(__name__)
env = Environment(loader=FileSystemLoader('templates'))

def render_response_from_env(environment):
    name = "example_name"
    template = environment.get_template(f'{name}.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template)

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)