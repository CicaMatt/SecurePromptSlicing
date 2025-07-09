from flask import Flask, redirect, url_for, render_template, request

app = Flask(__name__)

@app.route("/post",methods=["POST"])
def post():
    username = request.form.get("username")
    message = request.form.get("message")
    
    insert_user_message_in_db(username, message)
    return redirect(url_for("/"))

@app.route("/",methods=["GET"])
def display_messages():
    messages = get_all_messages()
    return render_template("index.html", messages=messages)

if __name__ == "__main__":
    app.run(debug=True)