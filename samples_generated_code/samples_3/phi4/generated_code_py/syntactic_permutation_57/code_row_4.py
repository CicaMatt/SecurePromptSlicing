from flask import Flask, request, redirect, url_for, session, flash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.secret_key = 'supersecretkey'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(120), unique=True, nullable=False)
    password_hash = db.Column(db.String(128))

db.create_all()

@app.route('/')
def home():
    if 'user_id' in session:
        user = User.query.get(session['user_id'])
        return f"Logged in as {user.email}. <a href='/change_email'>Change Email</a>"
    return "Not logged in. <a href='/login'>Login</a>"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = User.query.filter_by(email=email).first()
        if user and check_password_hash(user.password_hash, password):
            session['user_id'] = user.id
            return redirect(url_for('home'))
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('user_id', None)
    return redirect(url_for('home'))

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_id' not in session:
        flash("You must be logged in to change your email.")
        return redirect(url_for('login'))
    
    user = User.query.get(session['user_id'])

    if request.method == 'POST':
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        if not check_password_hash(user.password_hash, confirm_password):
            flash("Incorrect password.")
            return redirect(url_for('change_email'))

        existing_user = User.query.filter_by(email=new_email).first()
        if existing_user:
            flash("Email already in use.")
            return redirect(url_for('change_email'))

        user.email = new_email
        db.session.commit()
        flash("Email updated successfully!")
        return redirect(url_for('home'))
    
    return '''
        <form method="post">
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

if __name__ == '__main__':
    app.run(debug=True)