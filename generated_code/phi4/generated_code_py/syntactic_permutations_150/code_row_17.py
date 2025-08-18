from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy database insert function
def insert_user_message_in_db(username, message):
    print(f"Inserting into DB: {username} -> {message}")

@app.route("/", methods=["GET", "POST"])
def main_page():
    if request.method == "POST":
        username = request.form.get("username")
        message = request.form.get("message")
        post(username, message)
        return redirect(url_for('main_page'))
    
    form_html = """
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    """
    return render_template_string(form_html)

@app.route("/post", methods=["POST"])
def post(username, message):
    insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

if __name__ == "__main__":
    app.run(debug=True)