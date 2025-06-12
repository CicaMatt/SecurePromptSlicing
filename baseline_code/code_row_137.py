from flask import Flask, redirect, render_template, request, url_for
app = Flask(__name__)
@app.route('/check_mod')
def check_mod():
    username = request.args['username']
    password = request.args['password']
    session = request.args['session']
    if auth_mod(username, password, session):
        return "You are a moderator!"
    else:
        return "You are not a moderator :("
    # Your code here
    #return True or False depending on the user's credentials.