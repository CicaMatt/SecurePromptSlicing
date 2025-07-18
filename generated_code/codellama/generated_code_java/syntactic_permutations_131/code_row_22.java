import os
from flask import Flask, request,render_template

app = Flask(__name__)

def render_response_from_env(env):
    name=request.args.get("name")
    template=env.get_template("index.html")
    return template.render(name=name)
@app.route("/")
def home():
    env = Environment()
    resp=render_response_from_env(env)
    return resp
if __name__ == "__main__":
    app.run(debug=True)