from flask import Flask, render_template_string, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = f'<h1>Hello, {{ name }}!</h1>'
    rendered_template = render_template_string(template, name=name)
    return rendered_template

@app.route('/')
def home():
    env = {}  # Placeholder for any environment-specific variables
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)