from flask import Flask, request, Response

app = Flask(__name__)

def render_response_from_env(env):
    template = env.get_template('index.html')
    rendered_template = template.render(request.args.to_dict())
    return Response(rendered_template, mimetype='text/html')

def home():
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('templates'))
    response = render_response_from_env(env)
    return response

@app.route('/')
def index():
    return home()

if __name__ == '__main__':
    app.run()