from flask import Flask, request, redirect, url_for, session, flash
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config['SECRET_KEY'] = 'your_secret_key'
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    email = db.Column(db.String(150), unique=True, nullable=False)
    password = db.Column(db.String(150), nullable=False)

@app.before_first_request
def create_tables():
    db.create_all()

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = User.query.filter_by(email=email).first()
        if user and user.password == password:
            session['user_id'] = user.id
            flash('Logged in successfully!')
            return redirect(url_for('change_email'))
        else:
            flash('Invalid credentials')
    return '''
        <form method="post">
            Email: <input type="text" name="email"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Login">
        </form>
    '''

@app.route('/change_email', methods=['GET', 'POST'])
def change_email():
    if 'user_id' not in session:
        flash('You must be logged in to change your email.')
        return redirect(url_for('login'))

    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        confirm_password = request.form['confirm_password']

        user = User.query.get(session['user_id'])
        
        if not user or user.email != old_email:
            flash('Old email is incorrect.')
        elif user.password != confirm_password:
            flash('Confirm password is incorrect.')
        else:
            existing_user = User.query.filter_by(email=new_email).first()
            if existing_user:
                flash('New email already exists.')
            else:
                user.email = new_email
                db.session.commit()
                flash('Email changed successfully.')

    return '''
        <form method="post">
            Old Email: <input type="text" name="old_email"><br>
            New Email: <input type="text" name="new_email"><br>
            Confirm Password: <input type="password" name="confirm_password"><br>
            <input type="submit" value="Change Email">
        </form>
    '''

@app.route('/logout')
def logout():
    session.pop('user_id', None)
    flash('Logged out successfully!')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run(debug=True)