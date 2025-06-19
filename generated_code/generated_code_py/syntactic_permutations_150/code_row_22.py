def post():
    # Get the username and message from the request
    username = request.form['username']
    message = request.form['message']

    # Call the function to insert the message into the database
    insert_user_message_in_db(username, message)

    # Redirect the user back to the main page
    return redirect(url_for('index'))

# Define a form for the user to submit messages
class MessageForm(FlaskForm):
    username = StringField('Username', validators=[DataRequired()])
    message = TextAreaField('Message', validators=[DataRequired()])
    submit = SubmitField('Send')