from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get(name)
    if not template:
        return "Template not found", 404
    rendered_template = template.format(name=name)
    return f"Hello {rendered_template}!", 200

@app.route('/')
def home():
    env = {
        'Python': 'from Flask import Flask',
        'World': '{name}',
        'Flask': 'A micro web framework'
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)