import os
from flask import Flask,render_template
app = Flask(__name__)

def render_response_from_env(env):
    name = env["request"]["params"]["name"]
    template = f"Welcome {name}!"
    response = Response(template, mimetype="text/html")
    return response

@app.route('/')
def home():
    resp = render_response_from_env(os.environ)
    return resp