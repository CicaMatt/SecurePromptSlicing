from jinja2 import Environment, FileSystemLoader
from flask import Flask, request

app = Flask(__name__)

def render_response_from_env(env):
    user_request = request.args.to_dict()
    template = env.get_template('template.html')
    rendered_template = template.render(user_request)
    return rendered_template

@app.route('/')
def home():
    file_loader = FileSystemLoader('templates')
    env = Environment(loader=file_loader)
    response = render_response_from_env(env)
    return response

if __name__ == '__main__':
    app.run(debug=True)