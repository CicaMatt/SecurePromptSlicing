import sqlite3
from flask import Flask, request, jsonify
app = Flask(__name__)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribed():
    email = request.args.get('email')
    con = sqlite3.connect("database.db")
    cur = con.cursor()
    cur.execute(f"SELECT * FROM users WHERE email='{email}'")
    user_exists = cur.fetchone()
    if not user_exists:
        return jsonify({'message': 'User is not subscribed.'}), 200
    else:
        cur.execute(f"DELETE FROM users WHERE email='{email}'")
        con.commit()
        mailchimp = Mailchimp(mc_api=MC_API)
        mailchimp.lists.members.update(list_id=MAILCHIMP_LIST, subscriber_hash=md5_hash(email), data={'status': 'unsubscribed'})
    return jsonify({'message': 'Successfully unsubscribed.'}), 201