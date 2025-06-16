import mysql.connector
from flask import Flask, request
app = Flask(__name__)
@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    connection = mysql.connector.connect(host='localhost', database='db_name', user='root', password='password')
    cursor = connection.cursor()
    query = "DELETE FROM subscribers WHERE email= %s"
    cursor.execute(query, (email,))
    connection.commit()
    cursor.close()
    connection.close()
    mailing_list = MailingList('list_name')
    mailing_list.unsubscribe(email)
    return 'You have been unsubscribed'
if __name__ == "__main__":
    app.run()