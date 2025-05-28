from flask import Flask, render_template, request
    app = Flask(__name__)
    
    @app.route("/")
    def home():
        return render_template("home.html", title="Home", users=users, messages=messages)
    
    @app.route("/post", methods=["POST"])
    def post():
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username, message)
        return redirect("/")
    
    @app.route("/post", methods=["GET"])
    def show_posts():
        users = get_users()
        messages = get_messages()
        return render_template("home.html", title="Home", users=users, messages=messages)
    
    if __name__ == "__main__":
        app.run(debug=True)