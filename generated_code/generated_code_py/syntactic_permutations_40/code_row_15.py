from flask import Flask, session, redirect
app = Flask(__name__)
app.config["SECRET_KEY"] = "secret"
@app.route('/info')
def info():
  return session["username"] + "," + session["email"] + "," + session["ssn"][0:5]
if __name__ == '__main__':
  app.run()