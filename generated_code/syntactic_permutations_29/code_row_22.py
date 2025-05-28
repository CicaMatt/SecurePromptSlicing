import re
    from flask import Flask, redirect
    
    app = Flask(__name__)
    regex = r"example\.com"
    
    @app.route('/', defaults={'target': '/'})
    @app.route('/<path:target>')
    def route(target):
        if re.search(regex, target):
            return redirect('http://{}/'.format(target))
        else:
            return redirect('/')