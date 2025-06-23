@app.route("/", methods = ["GET","POST"])
def index():
    if request.method == "POST":
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username,message)
        return redirect("/")
    else:
        messages = get_messages()
        return render_template("index.html",messages = messages)
    
def insert_user_message_in_db(username, message):
    with sqlite3.connect("database.db") as db:
        db.execute("INSERT INTO messages (username,message) VALUES (?,?)",(username,message))
        db.commit()
        
def get_messages():
    with sqlite3.connect("database.db") as db:
        cursor = db.execute("SELECT * FROM messages ORDER BY ID DESC LIMIT 100")
        return cursor.fetchall()