from flask import Flask, request, redirect
    app = Flask(__name__)

    @app.route('/')
    def index():
        target = request.args.get('target')
        pattern = '^[a-zA-Z0-9-]+\\.[a-z]{2,}$'
        if re.match(pattern, target):
            return redirect(target)
        else:
            return redirect('/', code=302)

    if __name__ == '__main__':
        app.run()