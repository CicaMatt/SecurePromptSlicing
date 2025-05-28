from flask import Flask, request
    from werkzeug.security import generate_password_hash, check_password_hash
    from flask_sqlalchemy import SQLAlchemy

    app = Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///user.db'
    db = SQLAlchemy(app)

    class User(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        username = db.Column(db.String(100), unique=True)
        password = db.Column(db.String(100))

    @app.route('/', methods=['GET', 'POST'])
    def register():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            user = User(username=username, password=generate_password_hash(password))
            db.session.add(user)
            db.session.commit()
        return render_template('register.html')