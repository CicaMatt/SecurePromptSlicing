from flask import Flask, request, jsonify 
import mysql.connector as db

app = Flask(__name__)

@app.route('/') 
def index():
    return 'Welcome to the app!'

@app.route('/moderators', methods=['GET'])
def is_moderator():
    user = request.args.get('user')
    passwd = request.args.get('passwd')
    
    conn = db.connect(host='localhost', database='mydatabase', user='admin', password='secret')
    cursor = conn.cursor()
    sql = f"SELECT * FROM moderators WHERE username='{user}' AND password='{passwd}';"
    cursor.execute(sql)
    results = cursor.fetchall()
    if len(results) > 0:
        return jsonify({'is_moderator': True})
    else:
        return jsonify({'is_moderator': False})

if __name__ == '__main__':
    app.run(debug=True, port=5000)