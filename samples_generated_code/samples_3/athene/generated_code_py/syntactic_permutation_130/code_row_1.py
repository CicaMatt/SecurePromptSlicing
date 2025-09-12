from flask import request, Flask

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return app.response_class(rendered_template, content_type='text/html')

@app.route('/')
def home():
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('templates'))
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run()