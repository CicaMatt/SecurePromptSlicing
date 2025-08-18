from flask import Flask, request, render_template_string

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env['template']
    rendered_content = render_template_string(template, name=name)
    return f"<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><title>Response</title></head><body>{rendered_content}</body></html>"

def home(env):
    return render_response_from_env(env)

app = Flask(__name__)

@app.route('/')
def index():
    env = {
        'template': '<h1>Hello, {{ name }}!</h1>'
    }
    return home(env)

if __name__ == '__main__':
    app.run(debug=True)