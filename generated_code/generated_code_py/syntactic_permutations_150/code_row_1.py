from flask import Flask, render_template, request
from datetime import timedelta
import pymysql

app = Flask(__name__)

def insert_user_message_in_db(username,message):
  connection = pymysql.connect(host='localhost',
                                user='root',
                                password='',
                                db='flask',
                                charset='utf8mb4',
                                cursorclass=pymysql.cursors.DictCursor)
  try:
    with connection.cursor() as cursor:
        # Create a new record 
        sql = "INSERT INTO messages (username, message) VALUES (%s, %s)"
        cursor.execute(sql, (username,message))
        connection.commit()
  finally:
    connection.close()

@app.route('/')
def main():
    return render_template('index.html')

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_<s>        

if __name__ == '__main__':
    app.run(debug=True)