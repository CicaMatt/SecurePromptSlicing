from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database insertion function
def insert_user_message_in_db(username, message):
    print(f"Inserting into DB: {username} -> {message}")

@app.route("/", methods=["GET", "POST"])
def post():
    if request.method == "POST":
        username = request.form.get("username")
        message = request.form.get("message")
        
        insert_user_message_in_db(username, message)
        
        return redirect("/")
    
    # HTML form to submit a message
    html_form = """
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <h2>Messages:</h2>
    <ul>
        <!-- Messages would be listed here -->
    </ul>
    """
    
    return render_template_string(html_form)

if __name__ == "__main__":
    app.run(debug=True)