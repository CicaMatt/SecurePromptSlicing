import hashlib
from flask import Flask, request, redirect
app = Flask(__name__)
def insertIntoDatabase(username, hashedPassword, firstName, lastName, email):
    #code to connect to the database
    connection = sqlite3.connect('users.db')
    cursor = connection.cursor()
    if cursor.execute("SELECT username FROM users WHERE username= ?", (username,)) != []:
        return 'User already exists'
    else:
        cursor.execute("INSERT INTO users VALUES(?, ?, ?, ?)", (username, hashedPassword, firstName, lastName, email))
        connection.commit()
        connection.close()
        return "Registration successful!"

@app.route("/register", methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form('username')
        password = request.form('password')
        firstName = request.form('firstName')
        lastName = request.form('lastName')
        email = request.form('email')
        hashedPassword = hashlib.sha256(password.encode())
        return insertIntoDatabase(username, hashedPassword, firstName, lastName, email) 
    else:
        return render_template("register.html")
if __name__ == "__main__":
    app.run(debug=True)