from flask import Flask, request, render_template_string

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = f"Hello, {env} {{name}}!"
    return render_template_string(template, name=name)

@app.route('/')
def home():
    env = "Development"
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)