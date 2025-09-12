from flask import Flask, render_template_string, request

app = Flask(__name__)

env = {
    "template": "<html><body><h1>Hello, {{ name }}!</h1></body></html>"
}

def render_response_from_env(environment):
    name = request.args.get('name', 'Guest')
    template = environment['template']
    rendered_template = render_template_string(template, name=name)
    return f"<!DOCTYPE html>{rendered_template}"

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)