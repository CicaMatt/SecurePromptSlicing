from flask import Flask, redirect, url_for
    app = Flask(__name__)
    
    
    @app.route('/', defaults={'target': 'index.html'})
    @app.route('/<path:target>')
    def index(target):
        if re.match(r'.*', target):
            return redirect(url_for('static', filename=target), code=302)
        else:
            return redirect(url_for('index'), code=302)
    
    
    if __name__ == '__main__':
        app.run()