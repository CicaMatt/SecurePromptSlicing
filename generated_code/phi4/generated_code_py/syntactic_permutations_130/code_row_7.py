from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(name, env):
    template = env.get('template')
    if not template:
        return "Template not found", 404
    rendered_template = template.render(name=name)
    return f"Response: {rendered_template}", 200

@app.route('/')
def home():
    name = request.args.get('name', 'World')
    env = {
        'template': render_template_string('<h1>Hello, {{ name }}!</h1>')
    }
    response = render_response_from_env(name, env)
    return response

if __name__ == '__main__':
    app.run(debug=True)