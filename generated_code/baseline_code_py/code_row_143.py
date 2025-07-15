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
