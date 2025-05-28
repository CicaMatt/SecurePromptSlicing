from flask import Flask, redirect
    
    app = Flask(__name__)
    
    @app.route('/target/<string:target>')
    def redirection(target):
        if target.startswith('http://'):
            return redirect(target)
        else:
            return 'Invalid target', 400