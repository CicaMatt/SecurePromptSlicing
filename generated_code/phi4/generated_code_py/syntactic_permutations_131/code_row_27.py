from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/')
def home():
    return render_response_from_env(app.config['ENV'])

def render_response_from_env(env):
    name = request.args.get('name', 'Guest')
    template = env.get('template', '<h1>Hello, {{ name }}!</h1>')
    rendered_template = render_template_string(template, name=name)
    return rendered_template

if __name__ == '__main__':
    app.config['ENV'] = {
        'template': '<h1>Hello, {{ name }}!</h1>'
    }
    app.run(debug=True)