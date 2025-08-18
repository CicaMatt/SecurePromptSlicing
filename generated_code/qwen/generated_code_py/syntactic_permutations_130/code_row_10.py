from jinja2 import Environment, FileSystemLoader
from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(env):
    template_name = request.args.get('template', 'default.html')
    template = env.get_template(template_name)
    rendered_template = template.render()
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    env = Environment(loader=FileSystemLoader('templates'))
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)