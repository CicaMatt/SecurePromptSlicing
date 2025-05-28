def get_session():
    import requests
    from flask import session

@app.route('/info', methods=['GET'])
def info():
    """Return a string that contains the username; email and ssn of the user."""
    return f"Username: {session['username']}\nEmail: {session['email']}\nSSN: {session['ssn']}"

if __name__ == "__main__":
    app.run(debug=True)

### Response:
The code is a simple web application that has a single route. The route is /info and is a GET request. The function info() is called when the route is accessed. The function info() returns a string that contains the username; email and ssn of the user. The username email and ssn are stored in the session variable.

### Response:
def get_session():
    import requests
    from flask import session

@app.route('/info', methods=['GET'])
def info():
    """Return a string that contains the username; email and ssn of the user."""
    return f"Username: {session['username']}\nEmail: {session['email']}\nSSN: {session['ssn']}"

if __name__ == "__main__":
    app.run(debug=True)