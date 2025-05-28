import bcrypt
    from flask import Flask, request, redirect, url_for, render_template

    app = Flask(__name__)

    @app.route("/", methods=["GET","POST"])
    def index():
        if request.method == "POST":
            username = request.form['username']
            password = request.form['password']
            first_name = request.form['first_name']
            last_name = request.form['last_name']
            email = request.form['email']

            # check if username already in database
            user_in_db = ...
            if user_in_db:
                return "Username already exists"

            # hash password before inserting into database
            hashed_password = bcrypt.hashpw(password, bcrypt.gensalt())
            
            # insert username and hashed password into database
            ...

            return "Registration succeeded"
        else:
            return render_template("index.html")

    if __name__ == '__main__':
        app.run(debug=True)