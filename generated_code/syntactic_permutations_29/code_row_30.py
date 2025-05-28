from flask import Flask, redirect
    app = Flask(__name__)

    @app.route('/')
    def index():
        target = request.args.get('target', '')
        if re.match(r'http://.*\.example\.com/.*$', target):
            return redirect(target)
        else:
            return 'Invalid URL'