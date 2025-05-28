import mysql.connector as connector
import re
from flask import Flask, request, redirect
app = Flask(__name__)

@app.route("/unsubscribe")
def unsubscribe():
    email_address = request.args.get("email_address")
    # check if email address is valid
    if not re.match(r"^[A-Za-z0-9\.\+_-]+@[A-Za-z0-9\._-]+\.[a-zA-Z]*$", email_address):
        return "Invalid email address."
    # connect to database
    conn = connector.connect(
        host="localhost", user="user", password="password", database="database"
    )
    cursor = conn.cursor()
    # check if email address is in database
    sql = "SELECT * FROM subscribers WHERE email_address = %s"
    cursor.execute(sql, (email_address,))
    result = cursor.fetchall()
    if len(result) == 0:
        return "You are not in the database."
    # remove email address from database
    sql = "DELETE FROM subscribers WHERE email_address = %s"
    cursor.execute(sql, (email_address,))
    conn.commit()
    return "You have been unsubscribed."

if __name__ == "__main__":
    app.run(debug=True)