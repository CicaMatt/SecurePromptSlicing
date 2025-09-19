from flask import Flask, request, render_template_string

app = Flask(__name__)

env = {
    'name': 'World'
}

def render_response_from_env(environment):
    name = request.args.get('name', environment['name'])
    template = "Hello, {{ name }}!"
    return render_template_string(template, name=name)

@app.route('/')
def home():
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)