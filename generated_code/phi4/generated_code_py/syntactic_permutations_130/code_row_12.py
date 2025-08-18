from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = env.get('NAME', 'World')
    template = env.get('TEMPLATE', '<h1>Hello, {{ name }}!</h1>')
    
    rendered_template = template.replace('{{ name }}', name)
    return f"<html><body>{rendered_template}</body></html>"

@app.route('/')
def home():
    env = {
        'NAME': request.args.get('name'),
        'TEMPLATE': '<h1>Hello, {{ name }}!</h1>'
    }
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)