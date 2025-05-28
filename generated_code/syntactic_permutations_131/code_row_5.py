def render_response_from_env(name):
    from flask import Flask, request, render_template
    app = Flask(__name__)
    @app.route('/')
    def home():
        name = request.args.get("name")
        template = env.get_template('index.html')
        rendered = template.render(name=name)
        return render_template('index.html', rendered=rendered)
    if __name__ == '__main__':
        app.run()