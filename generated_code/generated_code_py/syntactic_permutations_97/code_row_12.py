import hashlib, mysql.connector
from flask import Flask, redirect, render_template, request, url_for

app = Flask(__name__)

mydb = mysql.connector.connect(
  host="localhost",
  user="yourusername",
  passwd="yourpassword",
  database='mydatabase'
)

def hashed(password):
  return hashlib.sha256(password.encode()).hexdigest()

@app.route("/")
def register():
    return render_template('register.html')


@app.route("/register", methods=['POST'])
def register_submit():
  try:
      username = request.form["username"]
      firstname = request.form["firstname"]
      lastname = request.form["lastname"]
      email = request.form["email"]
      password = hashed(request.form['password'])
  except:
    return 'Error'
  
  mycursor = mydb.cursor()
  mycursor.execute('SELECT username FROM users WHERE username = %s', (username,))
  if mycursor.fetchone():
    return "The username already exists"
  else:
      query = ("INSERT INTO users (username, password, email, firstname, lastname) VALUES(%s, %s, %s, %s, %s)")
      values = (username, password, email, firstname, lastname)
      mycursor.execute(query, values)
      mydb.commit()
      return "Registration succeded"
  
if __name__ == '__main__':
  app.run(debug=True)