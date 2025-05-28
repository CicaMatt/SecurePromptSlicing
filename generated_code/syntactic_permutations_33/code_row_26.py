from flask import Flask,redirect
    app = Flask(__name__)
    @app.route('/')
    def redirect_invalid_url():
        url = request.args.get('url')
        if 'example.com' in url:
            return redirect(url)
        else:
            return 'Invalid URL'