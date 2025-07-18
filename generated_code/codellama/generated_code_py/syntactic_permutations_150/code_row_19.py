from flask import Flask, request, redirect, url_for
app = Flask(__name__)
@app.route("/", methods=['GET', 'POST'])
def main():
    if request.method == 'GET':
        return '<html><body><form action="" method="post"><p>Message:</p><p><input name="message" /></p><p><input type="submit" value="Post it!" /></p></form></body></html>'
    else:
        post()
        return redirect(url_for('main'))
def insert_user_message_in_db():
    # Implement the function here, this is just a placeholder.
    pass