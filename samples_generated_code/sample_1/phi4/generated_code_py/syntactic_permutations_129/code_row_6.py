from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get(name, '<h1>Hello, {{ name }}!</h1>')
    rendered_template = render_template_string(template, name=name)
    return rendered_template

@app.route('/')
def home():
    env = {
        'home': '<h1>Welcome to the Home Page, {{ name }}!</h1>',
        'about': '<h1>About Us: We are {{ name }}\'s team.</h1>'
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)