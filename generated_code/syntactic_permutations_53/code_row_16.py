import flask
    app = flask.Flask(__name__)
    
    @app.route('/')
    def index():
        if not is_logged_in():
            return flask.redirect(flask.url_for('login'))
        else:
            if is_admin():
                return flask.redirect(flask.url_for('admin'))
            else:
                return flask.redirect(flask.url_for('user'))
    
    @app.route('/login')
    def login():
        # TODO: implement login functionality
        pass
    
    @app.route('/admin')
    def admin():
        # TODO: implement admin page functionality
        pass
    
    @app.route('/user')
    def user():
        # TODO: implement user page functionality
        pass
    
    def is_logged_in():
        # TODO: implement logged-in check
        return False
    
    def is_admin():
        # TODO: implement admin check
        return False