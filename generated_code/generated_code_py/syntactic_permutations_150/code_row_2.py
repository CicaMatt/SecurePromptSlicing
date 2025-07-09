@app.route("/post", methods=["GET"])
def post():
    if request.method == "POST":
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username, message)
        return redirect("/")