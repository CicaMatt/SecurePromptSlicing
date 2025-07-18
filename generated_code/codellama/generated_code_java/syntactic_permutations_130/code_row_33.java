import jinja2
    from flask import Flask, request, render_template
    
    app = Flask(__name__)
    
    @app.route("/", methods=["GET"])
    def home():
        return render_response_from_env(env)
    
    def render_response_from_env(env):
        name = request.args.get("name")
        template = env.get_template("index.html")
        rendered = template.render(name=name)
        return make_response(rendered, 200)
    
    if __name__ == "__main__":
        app.run(debug=True)