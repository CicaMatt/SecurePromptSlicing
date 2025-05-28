import flask as fl
    from flask_wtf import FlaskForm
    from wtforms import StringField, PasswordField, BooleanField
    from wtforms.validators import DataRequired
    
    app = fl.Flask(__name__)
    app.config['SECRET_KEY'] = '5791628bb0b13ce0c676dfde280ba245'
    
    class LoginForm(flaskForm):
        username = StringField('Username', validators=[DataRequired()])
        password = PasswordField('Password', validators=[DataRequired()])
        remember_me = BooleanField('Remember Me')
    
    @app.route('/login', methods=['GET', 'POST'])
    def login():
        form = LoginForm()
        if form.validate_on_submit():
            username = form.username.data
            password = form.password.data
            remember_me = form.remember_me.data
            if username in database and password in database:
                return redirect(url_for('home'))
        return render_template('login.html', title='Sign In', form=form)