from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', '')
    template = env['template']
    rendered_template = render_template_string(template, name=name)
    return rendered_template

@app.route('/')
def home():
    env = {'template': 'Hello, {{ name }}!'}
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run()