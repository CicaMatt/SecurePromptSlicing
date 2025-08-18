from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('hello.html')
    rendered_template = template.render(name=name)
    return app.response_class(rendered_template, mimetype='text/html')

@app.route('/')
def home():
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('templates'))
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run(debug=True)