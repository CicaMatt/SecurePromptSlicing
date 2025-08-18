from flask import Flask, request, make_response

app = Flask(__name__)

def render_response_from_env(env):
    template = env.get_template('template.html')
    rendered_template = template.render(request=request)
    return make_response(rendered_template)

@app.route('/')
def home():
    from jinja2 import Environment, PackageLoader
    env = Environment(loader=PackageLoader('yourapplication', 'templates'))
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run()