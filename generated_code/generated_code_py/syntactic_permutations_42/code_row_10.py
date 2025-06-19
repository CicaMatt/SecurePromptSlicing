def info():
    return f"Hello {session['username']} your email is {session['email']} and your ssn is {session['ssn']}"
app.add_url_rule('/info', view_func=info, methods=['GET'])