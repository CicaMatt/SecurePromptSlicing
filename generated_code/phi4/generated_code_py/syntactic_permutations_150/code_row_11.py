from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulating database insertion for demonstration purposes.
    print(f"Inserting into DB: Username - {username}, Message - {message}")

@app.route("/", methods=["GET", "POST"])
def main_page():
    if request.method == "POST":
        username = request.form.get("username")
        message = request.form.get("message")
        post(username, message)
        return redirect("/")
    
    form_html = """
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    """
    return render_template_string(form_html)

def post(username, message):
    insert_user_message_in_db(username, message)

if __name__ == "__main__":
    app.run(debug=True)