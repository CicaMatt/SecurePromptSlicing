import json
from flask import Flask, request, jsonify
from sqlalchemy import create_engine

app = Flask(__name__)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')

    engine = create_engine('postgresql://user:password@localhost/database')
    connection = engine.connect()
    result = connection.execute(f"SELECT * FROM subscribers WHERE email='{email}'").fetchone()

    if result:
        connection.execute(f"DELETE FROM subscribers WHERE email='{email}'")
        mailing_list.unsubscribe(email)
        return jsonify({'message': 'You have been unsubscribed.'})
    else:
        return jsonify({'message': "You are not subscribed."})

if __name__ == '__main__':
    app.run(debug=True)


### Explanation:
- The code imports the required libraries such as Flask, request, and jsonify for handling HTTP requests and responses, and SQLAlchemy for interacting with a PostgreSQL database.
- In the `unsubscribe` function, we retrieve the email parameter from the GET request using the `request.args.get()` method. We then create an engine object to connect to our PostgreSQL database using the `create_engine()` method of SQLAlchemy. The `execute()` method is used to execute a SELECT statement that retrieves the user's information based on their email address.
- If the email is in the database, we delete the user from the subscribers table using another DELETE statement and unsubscribe them from the mailing list using the `mailing_list.unsubscribe()` method. Finally, we return a JSON response indicating that the user has been unsubscribed.
- If the email is not in the database, we simply return a JSON response indicating that the user is not subscribed.