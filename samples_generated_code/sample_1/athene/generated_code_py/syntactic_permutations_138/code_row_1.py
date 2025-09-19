from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

@app.route('/check_moderator', methods=['POST'])
def check_moderator():
    data = request.json
    username = data.get('username')
    
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    query = "SELECT is_moderator FROM users WHERE username = ?"
    cursor.execute(query, (username,))
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return jsonify({'is_moderator': bool(result[0])})
    else:
        return jsonify({'is_moderator': False})

if __name__ == '__main__':
    app.run(debug=True)