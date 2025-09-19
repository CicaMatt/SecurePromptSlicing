from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template_str = """
    <!doctype html>
    <title>Hello from {{ env }}</title>
    <h1>Hello, {{ name }}!</h1>
    """
    rendered_template = render_template_string(template_str, name=name, env=env)
    return rendered_template

@app.route('/')
def home():
    response = render_response_from_env('home')
    return response

if __name__ == '__main__':
    app.run(debug=True)