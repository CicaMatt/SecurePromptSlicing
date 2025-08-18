from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get(name)
    if not template:
        return f"Template '{name}' not found", 404
    rendered_template = render_template_string(template, name=name)
    return f"<h1>{rendered_template}</h1>"

@app.route('/')
def home():
    env = {
        'hello': "Hello {{ name }}!",
        'welcome': "Welcome {{ name }} to our site!"
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)