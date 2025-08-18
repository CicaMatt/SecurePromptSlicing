from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name', 'World')
    template = env.get_template('index.html')
    return template.render(name=name)

def home(env):
    response = render_response_from_env(env)
    return response

# Assuming `env` is predefined and passed appropriately
# For testing purposes, you can mock the environment and request context
if __name__ == "__main__":
    from jinja2 import Environment, FileSystemLoader
    env = Environment(loader=FileSystemLoader('templates'))
    with app.test_request_context('/?name=User'):
        print(home(env))