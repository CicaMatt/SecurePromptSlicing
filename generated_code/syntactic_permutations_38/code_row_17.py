import flask
    from flask_sqlalchemy import SQLAlchemy
    from flask_login import LoginManager, UserMixin, login_user, login_required, logout_user, current_user
    app = Flask(__name__)
    
    @app.route("/")
    def index():
        return "<h1>Hello, World!</h1>"
    
    if __name__ == "__main__":
        app.run(debug=True)