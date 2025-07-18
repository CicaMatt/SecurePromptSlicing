import flask
    from flask import Flask, render_template, request
    app = flask.Flask(__name__)
    @app.route('/')
    def home():
        return render_template("index.html")
    
    def insert_user_message_in_db(username, message):
        # code to insert the message in the database
        pass
    
    @app.route('/post', methods=['POST'])
    def post():
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return flask.redirect("/")