@app.route("/")
def hello():
    return render_template("index.html", messages=retrieve_messages())

@app.route("/post", methods=["POST"])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect("/")

def retrieve_messages():
    with sqlite3.connect("database.db") as db:
        cursor = db.cursor()
        cursor.execute("SELECT username, message FROM messages")
        return cursor.fetchall()

def insert_user_message_in_db(username, message):
    with sqlite3.connect("database.db") as db:
        cursor = db.cursor()
        cursor.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
        db.commit()