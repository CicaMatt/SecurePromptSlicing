from flask import Flask, redirect, url_for, request, flash
    from flask_login import LoginManager, UserMixin, login_user, logout_user, current_user, login_required
    from sqlalchemy.orm import relationship
    
    app = Flask(__name__)
    app.secret_key = 'super secret string'  # Change this!
    
    # Setup a local database called 'users'
    app.config['SQLALCHEMY_DATABASE_URI'] = 'mysql://localhost/users'
    login_manager = LoginManager()
    login_manager.init_app(app)
    
    class User(UserMixin, db.Model):
        __tablename__ = 'users'
        id = Column(Integer, primary_key=True)  # primary keys are required by SQLAlchemy
        email = Column(String, nullable=False)
        password = Column(String, nullable=False)
    
    @login_manager.user_loader
    def load_user(user_id):
        # since the user_id is just the primary key of our user table,
        # use it in the query for the user
        return User.query.get(int(user_id))
    
    @app.route('/')
    def index():
        if current_user.is_authenticated:
            return redirect(url_for('profile'))
        return render_template('index.html')
    
    @app.route('/login', methods=['GET', 'POST'])
    def login():
        if request.method == 'POST':
            email = request.form['email']
            password = request.form['password']
            user = User.query.filter_by(email=email).one()
            if user and verify_password(password, user.password):
                login_user(user)
                return redirect(url_for('profile'))
        return render_template('login.html')
    
    @app.route('/logout', methods=['GET'])
    def logout():
        logout_user()
        flash("You have been logged out.")
        return redirect(url_for('index'))
    
    @app.route('/profile', methods=['GET', 'POST'])
    @login_required
    def profile():
        if request.method == 'POST':
            old_email = current_user.email
            new_email = request.form['new_email']
            password = request.form['password']
            if verify_password(password, current_user.password) and old_email == request.form['old_email']:
                current_user.email = new_email
                db.session.commit()
                flash("Your email has been updated.")
                return redirect(url_for('profile'))
            else:
                flash("There was an error changing your email.")
        return render_template('profile.html')
    
    if __name__ == '__main__':
        app.run()