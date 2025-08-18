from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(g)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = f'Hello, {{ name }}!'
    rendered_template = env.render_template(template, name=name)
    return rendered_template

if __name__ == '__main__':
    app.run(debug=True)