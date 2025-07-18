import random
import string
from flask import Flask, redirect, url_for, request

app = Flask(__name__)

users = {
  "test@example.com": "test"
}

sessions = {}

def generate_otp():
  digits = "0123456789"
  otp = ""
  for i in range(6):
    otp += digits[random.randint(0, len(digits)-1)]
  return otp

@app.route("/")
def index():
  session_id = request.cookies.get("session_id")
  if not session_id:
    return redirect(url_for("login"))
  user_data = sessions.get(session_id)
  if not user_data:
    return redirect(url_for("login"))
  return "Welcome, {}! <a href=\"/logout\">Logout</a>".format(user_data["email"])

@app.route("/login", methods=["GET", "POST"])
def login():
  if request.method == "POST":
    email = request.form["email"]
    password = request.form["password"]
    if email not in users or users[email] != password:
      return redirect(url_for("login"))
    session_id = ''.join(random.choice(string.ascii_letters + string.digits) for i in range(16))
    sessions[session_id] = {"email": email}
    response = redirect(url_for("index"))
    response.set_cookie("session_id", session_id)
    return response
  return """
    <form method="post">
      <label for="email">Email:</label>
      <input type="text" name="email"><br>
      <label for="password">Password:</label>
      <input type="password" name="password"><br>
      <button>Submit</button>
    </form>
  """

@app.route("/logout", methods=["POST"])
def logout():
  session_id = request.cookies.get("session_id")
  if session_id:
    del sessions[session_id]
  response = redirect(url_for("index"))
  response.set_cookie("session_id", "", expires=0)
  return response

@app.route("/change_email/<old_email>", methods=["GET", "POST"])
def change_email(old_email):
  if request.method == "POST":
    new_email = request.form["new_email"]
    otp = request.form["otp"]
    if old_email not in users or users[old_email] != otp:
      return redirect(url_for("login"))
    users[new_email] = users[old_email]
    del users[old_email]
    response = redirect(url_for("index"))
    return response
  session_id = request.cookies.get("session_id")
  if not session_id:
    return redirect(url_for("login"))
  user_data = sessions.get(session_id)
  if not user_data:
    return redirect(url_for("login"))
  otp = generate_otp()
  users[user_data["email"]] = otp
  return """
    <form method="post">
      <label for="new_email">New Email:</label>
      <input type="text" name="new_email"><br>
      <label for="otp">OTP:</label>
      <input type="text" name="otp"><br>
      <button>Submit</button>
    </form>
  """