from flask import Flask, render_template, request
app = Flask(__name__)
@app.route("/")
def home():
    return render_response_from_env(request.environ)
def render_response_from_env(env):
    name = request.args.get("name")
    template = env.get_template("index.html")
    rendered_template = template.render(name=name)
    return Response(rendered_template, mimetype="text/html")
if __name__ == "__main__":
    app.run()