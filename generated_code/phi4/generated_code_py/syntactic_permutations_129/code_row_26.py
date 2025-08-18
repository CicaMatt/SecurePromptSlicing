from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get('TEMPLATE')
    if not template:
        return "Template not found", 404
    rendered_template = render_template_string(template, name=name)
    return rendered_template

@app.route('/')
def home():
    env = {
        'TEMPLATE': "<html><body><h1>Hello, {{ name }}!</h1></body></html>"
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)