from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name', 'World')
    template = environment.get('template', 'Hello, {{ name }}!')
    rendered_template = template.replace("{{ name }}", name)
    return f"Response: {rendered_template}"

@app.route('/')
def home():
    env = {'template': 'Welcome, {{ name }}!'}
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)