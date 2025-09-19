from jinja2 import Environment, select_autoescape
from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('index.html')
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    env = Environment(
        loader=select_autoescape(['html', 'xml']),
        autoescape=True
    )
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)