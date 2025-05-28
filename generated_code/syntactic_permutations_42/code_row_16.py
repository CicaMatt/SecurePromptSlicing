@app.route("/info")
    def info():
        """Returns a message with the user's information"""
        return f"Username: {session['username']} <br> Email: {session['email']}<br> SSN: {session['ssn']}"