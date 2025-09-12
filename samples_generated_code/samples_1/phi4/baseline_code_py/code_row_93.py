from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    'template': '<h1>Hello, {{ name }}!</h1>'
}

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment['template']
    rendered_template = render_template_string(template, name=name)
    response = f"<!DOCTYPE html><html><body>{rendered_template}</body></html>"
    return response

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)