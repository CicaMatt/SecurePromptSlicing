@app.route("/", methods=["GET"])
def login():
    return "<form action="do_login" method="POST"><input type="text" name="name"></br><input type="password" name="password"></br> <button type="submit">Submit</button></form>"

@app.route("/", methods=["POST"])
def do_login():
    if request.form['name'] == 'admin' and request.form['password'] == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return "Invalid credentials"