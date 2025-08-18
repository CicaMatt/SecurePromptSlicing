from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'Guest')
    template = environment.get('template', 'Hello, {{ name }}!')
    return render_template_string(template, name=name)

@app.route('/')
def index():
    environment = {
        'template': '<h1>Hello, {{ name }}!</h1>'
    }
    return render_response_from_env(environment)

if __name__ == '__main__':
    app.run(debug=True)