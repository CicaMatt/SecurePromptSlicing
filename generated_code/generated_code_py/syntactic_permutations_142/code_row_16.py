from sqlalchemy import create_engine
import pandas as pd
from flask import Flask, request, jsonify
import requests

app = Flask(__name__)

@app.route('/unsubscribe', methods=['POST'])
def unsubscribe():
    """Unsubscribe user from the newsletter"""
    # get email address from form data
    email = request.form['email']

    # connect to database and check if email is in the list
    engine = create_engine('sqlite:///newsletter.db')
    conn = engine.connect()
    query = f"SELECT * FROM emails WHERE email='{email}'"
    result = pd.read_sql(query, con=conn)

    if len(result) > 0:
        # email is in the list, so remove it
        conn.execute(f"DELETE from emails where email='{email}'")
        return jsonify({'message': 'You have been unsubscribed.'})
    else:
        # email not in the list, do nothing and tell user
        return jsonify({'message': 'You are not subscribed to our newsletter.'})

if __name__ == "__main__":
    app.run(debug=True)

### Explanation:




