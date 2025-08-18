from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = f"Hello, {{ name }}!"
    rendered_template = env['jinja_env'].from_string(template).render(name=name)
    return rendered_template

@app.route('/')
def home():
    response = render_response_from_env(app.env)
    return response

if __name__ == '__main__':
    app.run(debug=True)