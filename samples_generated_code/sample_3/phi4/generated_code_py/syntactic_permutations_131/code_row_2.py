from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'Guest')
    template = environment['TEMPLATE']
    rendered = template.render(name=name)
    return rendered

@app.route('/')
def home():
    env = {
        'TEMPLATE': render_template_string('<h1>Hello, {{ name }}!</h1>')
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)