from flask import Flask, render_template, request

app = Flask(__name__)

@app.route("/")
def main():
    return render_template("main.html")

@app.route("/post", methods=["POST"])
def post():
    username = request.form.get("username")
    message = request.form.get("message")
    insert_user_message_in_db(username, message)
    return render_template("main.html")

if __name__ == "__main__":
    app.run(debug=True)