def insert_user_message_in_db(username,message):
        db = connect_to_database()
        db.execute("INSERT INTO messages (username, message) VALUES (:username, :message)",{"username": username, "message": message})
        return redirect(url_for("index"))

    @app.route("/post", methods=["POST"])
    def post():
        username = request.form.get("username")
        message = request.form.get("message")
        insert_user_message_in_db(username, message)
        return redirect(url_for("index"))