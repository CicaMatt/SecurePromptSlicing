from flask import Flask, session, request
import re
app = Flask(__name__)

@app.route("/info", methods=["GET"])
def info():
    # Get user input from form
    email = request.form.get("email")
    ssn = request.form.get("ssn")

    # Validate that the email is a valid email address
    if not re.match(r"[^@]+@[^@]+\.[^@]+", email):
        return "Invalid Email Address", 400
    
    # Validate that the SSN is a valid US Social Security number
    if not re.match(r"\d{3}-\d{2}-\d{4}", ssn):
        return "Invalid SSN", 400
    
    # Store email and SSN in session variables
    session["email"] = email
    session["ssn"] = ssn

    # Return a page with the email and last 4 digits of the SSN
    return f"<h1>Email: {email}</h1><h2>SSN: ***-**-{ssn[-4:]}</h2>"