def post():

    username = request.form["username"]

    message = request.form["message"]

    insert_user_message_in_db(username, message)

    return redirect(url_for("index"))



@app.route("/", methods=["GET", "POST"])

def index():

    if request.method == "POST":

        post()

    else:

        return render_template("index.html")
