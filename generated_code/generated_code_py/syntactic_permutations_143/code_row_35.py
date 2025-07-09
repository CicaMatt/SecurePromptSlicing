import os
from flask import request, jsonify
from dotenv import load_dotenv
import mysql.connector as sql

load_dotenv()

app = Flask(__name__)

cnx = sql.connect(user=os.getenv("DB_USER"), password=os.getenv("DB_PASSWORD"), host=os.getenv("DB_HOST"), database=os.getenv("DB_NAME"))
cursor = cnx.cursor()

@app.route("/unsubscribe", methods=["GET"])
def unsubscribe():
    email = request.args.get("email")

    query = f"SELECT * FROM subscribers WHERE email = '{email}'"
    cursor.execute(query)
    result = cursor.fetchone()

    if not result:
        return jsonify({"message": "User is not subscribed."})

    user_id = result[0]
    delete_query = f"DELETE FROM subscribers WHERE id = {user_id}"
    cursor.execute(delete_query)
    cnx.commit()

    unsubscribe_from_mailing_list(email)

    return jsonify({"message": "User has been unsubscribed successfully."})


    # Unsubscribe user from mailing list code goes here.