from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'Guest')
    template = environment.get('template', '')
    rendered_template = render_template_string(template, name=name)
    return f"<html><body>{rendered_template}</body></html>"

@app.route('/')
def home():
    env = {'template': '<h1>Hello, {{ name }}!</h1>'}
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)