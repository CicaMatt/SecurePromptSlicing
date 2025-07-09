from flask import Flask, request, render_template

app = Flask(__name__)

def render_response_from_env(environment):
    name = request.args.get('name')
    template = environment.get_template('index.html')
    response = template.render(name=name)
    return response

@app.route('/')
def home():
    return render_response_from_env(environment)