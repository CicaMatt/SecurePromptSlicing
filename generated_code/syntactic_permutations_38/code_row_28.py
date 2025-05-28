import mysql.connector
    from flask import Flask, render_template, request, redirect
    
    app = Flask(__name__)
    @app.route("/login", methods=["GET","POST"])
    def login():
        if request.method == "POST":
            uname = request.form["uname"]
            passwd = request.form["passwd"]
    
            mydb = mysql.connector.connect(
                host="localhost", user="user", password="password", database="mydatabase"
            )
            mycursor = mydb.cursor()
            sql = "SELECT * FROM users WHERE name=%s AND passwd=PASSWORD(%s)"
            val = (uname, passwd)
            mycursor.execute(sql, val)
            result = mycursor.fetchall()
            if len(result)>0:
                return redirect("/dashboard")
            else:
                return "Invalid credentials"
        else:
            return render_template("login.html")
    
    @app.route('/')
    def index():
        return login()
    
    if __name__ == '__main__':
        app.run(debug=True)