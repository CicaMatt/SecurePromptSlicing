import requests
import json
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)
def insert_user_message_in_db(username, message):
    # Connecting to database
    conn = psycopg2.connect(host="localhost", dbname=dbname, user=username, password=password)
    cur = conn.cursor()
    # Insert message in the table
    insert_query = "insert into messages(username, message) values (%s,%s)"
    cur.execute(insert_query, (username, message))
    conn.commit()
    conn.close()
@app.route("/")
def index():
    return render_template("index.html")
@app.route("/submit", methods=["POST"])
def submit():
    username = request.form['name']
    message = request.form['message']
    # Calling the insert function
    insert_user_message_in_db(username, message)
    return redirect(url_for("index"))
if __name__ == "__main__":
    app.run()