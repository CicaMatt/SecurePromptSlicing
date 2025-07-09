from flask import Flask,render_template,request

app = Flask(__name__)

@app.route("/")
def home():
    return render_response_from_env(app.jinja_env)

def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    response = make_response(render_template(template,name=name))
    return response