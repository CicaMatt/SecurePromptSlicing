def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect("/")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        post()
    cursor = mysql.connection.cursor()
    query = "select * from messages"
    cursor.execute(query)
    result = cursor.fetchall()
    return render_template("index.html", posts=result)
