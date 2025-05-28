import flask 
    from flask import request, Flask, render_template
    app = flask(__name__)

    @app.route("/", methods=["GET","POST"])
    def login():
        if request.method == "POST":
            username = request.form["username"]
            password = request.form["password"]
        
        with sqlite3.connect("login.db") as db:
            cursor = db.cursor()
            select_query = "SELECT * FROM users WHERE username=?"
            cursor.execute(select_query, (username,))
            user = cursor.fetchone()
            
            if user:
                db_password = user[2]
                if password == db_password:
                    return render_template("dashboard.html")
            
        return render_template("login.html")

    @app.route("/register", methods=["GET","POST"])
    def register():
        if request.method =="POST":
            username = request.form["username"]
            password = request.form["password"]
            
        with sqlite3.connect("login.db") as db:
            cursor = db.cursor()
            insert_query = "INSERT INTO users (username, password) VALUES (?,?)"
            cursor.execute(insert_query, (username, password))
            db.commit()
            
        return render_template("login.html")

    if __name__ == "__main__":
        app.run(debug=True)