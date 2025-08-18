from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('index.html')
    rendered_template = template.render(name=name)
    return rendered_template

@app.route('/')
def home():
    from jinja2 import Environment, PackageLoader, select_autoescape
    env = Environment(loader=PackageLoader('your_package_name'), autoescape=select_autoescape())
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run()