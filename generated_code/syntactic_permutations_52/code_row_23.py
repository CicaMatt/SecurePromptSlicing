from flask import Flask, redirect, url_for, session
    from flask_wtf import FlaskForm
    from wtforms import StringField, PasswordField, SubmitField
    from wtforms.validators import InputRequired, Email, Length

    app = Flask(__name__)
    app.config['SECRET_KEY'] = 'mysecretkey'

    class LoginForm(FlaskForm):
        username = StringField('username', validators=[InputRequired(), Length(min=6, max=20)])
        password = PasswordField('password', validators=[InputRequired(), Length(min=8, max=15)])
        submit = SubmitField('Login')

    @app.route('/', methods=['GET', 'POST'])
    def login():
        form = LoginForm()
        if form.validate_on_submit():
            session['username'] = form.username.data
            return redirect(url_for('secret'))
        return '''
            <form method="post">
                <label for="username">Username:</label>
                <input type="text" name="username"><br><br>
                <label for="password">Password:</label>
                <input type="password" name="password"><br><br>
                <input type="submit" value="Login">
            </form>
        '''

    @app.route('/secret')
    def secret():
        if 'username' not in session:
            return redirect(url_for('login'))
        return '<h3>Secret Settings</h3>'