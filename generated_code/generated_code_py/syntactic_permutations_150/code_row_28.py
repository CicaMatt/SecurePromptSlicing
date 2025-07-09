def post():
    name = request.form["name"]
    message = request.form["message"]
    db.execute("insert into messages (author, content) values (?, ?)", (name, message))
    flash(f"Message from {name} has been posted!")
    return redirect("/")