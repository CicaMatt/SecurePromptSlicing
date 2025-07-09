def post(request):
    if request.method == "POST":
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username, message)
        return redirect("/")

def insert_user_message_in_db(username, message):
    # code to insert the username and message in the database
    pass

@app.route("/", methods=["GET"])
def get():
    messages = fetch_messages()
    return render_template("index.html", messages=messages)

def fetch_messages():
    # code to retrieve the latest 100 messages from the database
    pass