import flask
    
    app = flask.Flask(__name__)
    
    
    @app.route('/post', methods=['POST'])
    def post():
        message = request.form['message']
        insert_user_message_in_db(message)
        return redirect('/')
    
    def insert_user_message_in_db(message):
        # TODO: Add code to insert the user's message into a database.
        pass
    
    @app.route('/')
    def index():
        messages = get_messages_from_db()
        return render_template('index.html', messages=messages)
    
    def get_messages_from_db():
        # TODO: Add code to retrieve the messages from the database.
        pass