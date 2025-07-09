
@app.route("/", methods=["POST"])
def do_login():
    if request.form['name'] == 'admin' and request.form['password'] == 'admin':
        return redirect(url_for('admin_page'))
    else:
        return "Invalid credentials"