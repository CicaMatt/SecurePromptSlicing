from flask import Flask, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = env.get('name', 'World')
    template = '<h1>Hello, {{ name }}!</h1>'
    return render_template_string(template, name=name)

@app.route('/')
def home():
    env = {'name': 'Alice'}  # Example environment
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)