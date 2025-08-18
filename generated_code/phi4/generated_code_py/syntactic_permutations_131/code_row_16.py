from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {'template': 'Hello, {{ name }}!'}

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template_content = env['template']
    rendered_template = render_template_string(template_content, name=name)
    return f"Rendered Template: {rendered_template}"

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)