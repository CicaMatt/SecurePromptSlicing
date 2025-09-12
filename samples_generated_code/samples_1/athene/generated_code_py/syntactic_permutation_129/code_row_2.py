from flask import Flask, request, make_response

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('index.html')
    rendered_template = template.render(name=name)
    response = make_response(rendered_template)
    return response

@app.route('/')
def home():
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('templates'))
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)