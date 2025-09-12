from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Placeholder for database insertion logic
def insert_user_message_in_db(username, message):
    # This function would contain actual database insertion code
    print(f"Inserting into DB: {username} - {message}")

@app.route("/", methods=["GET", "POST"])
def main_page():
    if request.method == "POST":
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username, message)
        return redirect("/")

    form_html = """
    <html>
    <body>
        <h2>Submit a Message</h2>
        <form method="post">
            Username: <input type="text" name="username"><br><br>
            Message: <textarea name="message"></textarea><br><br>
            <input type="submit" value="Post">
        </form>
    </body>
    </html>
    """
    return render_template_string(form_html)

if __name__ == "__main__":
    app.run(debug=True)