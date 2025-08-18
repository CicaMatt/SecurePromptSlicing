from flask import Flask, render_template_string, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template_str = env['TEMPLATE']
    rendered_content = render_template_string(template_str, name=name)
    return f"<!doctype html><html><body>{rendered_content}</body></html>"

@app.route('/')
def home():
    env = {'TEMPLATE': '<h1>Hello, {{ name }}!</h1>'}
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)