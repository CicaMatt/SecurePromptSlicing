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
In this response, the Flask application is first imported along with its dependencies. A new Flask instance is created and an unsubscribe function is defined at the root URL with a POST request method.
The email address input by the user from the form data is then retrieved using the request module's form property.
Next, a database connection is established using SQLAlchemy's create_engine function. The connection is used to query the emails table for the email entered by the user.
If the email exists in the database, it is removed by executing a delete statement on the database connection. A JSON response is then returned to the user stating that they have been unsubscribed.
If the email does not exist in the database, a JSON response is returned informing the user that they are not subscribed to the newsletter.