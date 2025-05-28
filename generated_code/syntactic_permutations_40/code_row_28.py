import flask
    
    app = flask.Flask(__name__)
    app.config["DEBUG"] = True
    
    @app.route('/info', methods=['GET'])
    def info():
        email = flask.session['username']
        ssn = flask.session['ssn'][-4:]
        return f"{email} {ssn}"
        
    if __name__ == '__main__':
        app.run()