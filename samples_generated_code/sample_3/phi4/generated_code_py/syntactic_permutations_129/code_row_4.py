from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html')
    rendered_template = template.render(name=name)
    return f"Response: {rendered_template}"

@app.route('/')
def home():
    from jinja2 import Environment, PackageLoader
    env = Environment(loader=PackageLoader('your_package_name', 'templates'))
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)