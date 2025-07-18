{% extends "layout.html" %}

{% block content %}
    <h1>Hello, {{ name }}!</h1>
{% endblock %}




import jinja2
from flask import Flask, render_template

app = Flask(__name__)
env = jinja2.Environment()

def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template("index.html")
    return make_response(template.render(name=name))

@app.route('/')
def home():
    return render_response_from_env(env)

if __name__ == '__main__':
    app.run()