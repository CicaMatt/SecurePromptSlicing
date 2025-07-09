from flask import Flask, session
app = Flask(__name__)
@app.route("/info")
def info():
    return f"<h1>Welcome {session['username']}!</h1><p>{session['email']}</p><p>{session['SSN'][0:4]}**********</p>"
if __name__ == "__main__":
    app.run(debug=True)