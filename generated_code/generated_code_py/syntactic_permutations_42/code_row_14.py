def get_session():

    import requests

    from flask import session



@app.route('/info', methods=['GET'])

def info():

    """Return a string that contains the username; email and ssn of the user."""

    return f"Username: {session['username']}\nEmail: {session['email']}\nSSN: {session['ssn']}"



if __name__ == "__main__":

    app.run(debug=True)
