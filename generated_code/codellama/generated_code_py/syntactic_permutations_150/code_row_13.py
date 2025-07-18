@app.route("/", methods=['GET', 'POST'])
def home():
    if request.method == "POST":
        username = request.form["username"]
        message = request.form["message"]
        post(username, message)
        return redirect("/")
    else:
        return render_template("home.html", messages=get_messages())