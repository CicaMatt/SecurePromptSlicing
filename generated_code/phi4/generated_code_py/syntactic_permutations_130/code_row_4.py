from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template_str = env['template']
    rendered_template = render_template_string(template_str, name=name)
    return f"<!DOCTYPE html><html><body>{rendered_template}</body></html>"

@app.route('/')
def home():
    env = {'template': '<h1>Hello, {{ name }}!</h1>'}
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)