from flask import Flask, render_template, request
app = Flask(__name__)

@app.route('/')
def index():
    return "Hello World!"

@app.route('/change_email', methods=['POST'])
def change_email():
    if request.method == 'POST':
        old_email = request.form['old-email']
        new_email = request.form['new-email']
        password = request.form['password']

        # check if user is logged in
        if session['logged_in']:
            # check if email exists in database
            if db.session.query(User).filter_by(email=old_email).first():
                # check if password matches
                if bcrypt.checkpw(password, user.password):
                    # update email address in database
                    user.email = new_email
                    db.session.commit()
                    return 'Your email has been updated.'
                else:
                    return 'Incorrect password.'
            else:
                return 'Email not found.'
        else:
            return 'You must be logged in to change your email.'
    return "Hello World!"

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        user = db.session.query(User).filter_by(email=email).first()
        # check if user exists in database
        if user:
            # check if password matches
            if bcrypt.checkpw(password, user.password):
                session['logged_in'] = True
                return 'You are logged in.'
            else:
                return 'Incorrect password.'
        else:
            return 'User not found.'
    return "Hello World!"