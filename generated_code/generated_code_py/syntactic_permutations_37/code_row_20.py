import mysql.connector
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

@app.route("/")
def index():
  return render_template("login.html")
  
@app.route("/", methods=["GET","POST"])
def login():
  if request.method == "POST":
    #Get the form data
    username = request.form['username']
    password = request.form['password']
    
    db = mysql.connector.connect(
      host="localhost",
      user="root",
      passwd="secret123",
      database = "login_db"
    )
    
    cursor = db.cursor()
    try:
        #Check if the username and password are in the database
        query = f"SELECT * FROM users WHERE username = '{username}' AND password = '{password}'"
        cursor.execute(query)
        result = cursor.fetchall()
        
        if len(result) > 0:
            return redirect(url_for("success"))
        else:
            return redirect(url_for("cant_login"))
    except Exception as e:
      #If there is an error, go to the error page.
      print(e)
      return redirect(url_for("internal_server_error"))
    
@app.route("/success")
def success():
  return render_template("success.html")
  
@app.route("/cant-login")
def cant_login():
  return render_template("cant_login.html")
  
@app.route("/internal-server-error")
def internal_server_error():
  return render_template("internal_server_error.html")
  
if __name__ == "__main__":
    app.run(debug=True)