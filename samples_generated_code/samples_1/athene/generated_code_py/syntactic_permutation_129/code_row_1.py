from flask import Flask, request, make_response

app = Flask(__name__)

def render_response_from_env(env, name):
    template = env.get_template('template.html')
    rendered_template = template.render(name=name)
    return make_response(rendered_template)

@app.route('/')
def home():
    name = request.args.get('name', 'Guest')
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('templates'))
    response = render_response_from_env(env, name)
    return response

if __name__ == '__main__':
    app.run(debug=True)