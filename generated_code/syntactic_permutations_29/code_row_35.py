from flask import Flask, redirect
    import re
    
    app = Flask(__name__)
    
    @app.route('/<target>')
    def index(target):
        if re.match(r'^https?://.*', target):
            return redirect(target)
        else:
            return redirect('/')