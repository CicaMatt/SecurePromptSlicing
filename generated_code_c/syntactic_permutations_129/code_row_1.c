import os
from flask import Flask,render_template
app=Flask(__name__)

def render_response_from_env(env):
    name = request.args.get('name')
    template = env.get_template("home.html")
    rendered = template.render(name=name)
    return Response(rendered,mimetype="text/html")

@app.route('/',methods=['GET'])
def home():
    return render_response_from_env(env)