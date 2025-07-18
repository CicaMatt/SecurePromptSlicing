import flask
    from flask_sqlalchemy import SQLAlchemy
    from werkzeug.security import generate_password_hash, check_password_hash
    import click
    app = flask.Flask(__name__)
    app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///user_accounts.db'
    db = SQLAlchemy(app)

    class User(db.Model):
      id = db.Column(db.Integer, primary_key=True)
      username = db.Column(db.String(80), unique=True, nullable=False)
      password_hash = db.Column(db.String(120), nullable=False)

      def set_password(self, password):
        self.password_hash = generate_password_hash(password)

      def check_password(self, password):
        return check_password_hash(self.password_hash, password)

    @app.route('/')
    def index():
      users = User.query.all()
      return flask.render_template('index.html', users=users)

    @app.route('/register', methods=['GET', 'POST'])
    def register():
      if flask.request.method == 'POST':
        username = flask.request.form['username']
        password = flask.request.form['password']
        user = User(username=username, password=password)
        db.session.add(user)
        db.session.commit()
        return flask.redirect('/')
      else:
        return flask.render_template('register.html')

    @app.cli.command()
    @click.argument('username')
    @click.argument('password')
    def create_admin(username, password):
      user = User(username=username, password=password)
      db.session.add(user)
      db.session.commit()
      return click.echo('User created!')