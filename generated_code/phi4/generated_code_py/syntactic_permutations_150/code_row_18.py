from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database insert function
def insert_user_message_in_db(username, message):
    # This is where you would implement logic to insert data into a real database
    print(f"Inserting into DB: {username}, {message}")

@app.route("/", methods=["GET", "POST"])
def post():
    if request.method == "POST":
        username = request.form.get("username")
        message = request.form.get("message")
        insert_user_message_in_db(username, message)
        return redirect("/")
    
    # Main page with form
    html_form = """
    <html>
        <body>
            <h1>Submit a Message</h1>
            <form method="post">
                Username: <input type="text" name="username"><br>
                Message: <textarea name="message"></textarea><br>
                <input type="submit" value="Submit">
            </form>
        </body>
    </html>
    """
    
    return render_template_string(html_form)

if __name__ == "__main__":
    app.run(debug=True)