from flask import Flask, render_template, request, session
    
    app = Flask(__name__)
    
    @app.route("/info", methods=["GET"])
    def info():
        username = session['username']
        email = session['email']
        ssn = session['ssn']
        return render_template("userprofile.html", username=username, email=email, ssn=ssn)
    
    if __name__ == "__main__":
        app.run(debug=True)