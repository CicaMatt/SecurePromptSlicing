# import dependencies
    from flask import Flask, request, redirect, url_for, render_template
    from flask_sqlalchemy import SQLAlchemy

    app = Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///login.db'
    db = SQLAlchemy(app)

    # define database tables
    class User(db.Model):
        id = db.Column(db.Integer, primary_key=True)
        username = db.Column(db.String(80), unique=True, nullable=False)
        email = db.Column(db.String(120), unique=True, nullable=False)
        password = db.Column(db.String(64), nullable=False)

    @app.route('/', methods=['GET', 'POST'])
    def login():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            error = None
            user = User.query.filter_by(username=username).first()

            if user is None:
                error = 'Incorrect username.'
            elif not check_password_hash(user.password, password):
                error = 'Incorrect password.'

            if error is None:
                return redirect(url_for('index'))
            else:
                return render_template('login.html', error=error)
        return render_template('login.html')