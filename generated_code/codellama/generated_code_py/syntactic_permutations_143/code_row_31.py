from flask import Flask, request, jsonify
from sqlalchemy import create_engine
import psycopg2

app = Flask(__name__)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email is None:
        return jsonify({'error': 'Email parameter required'}), 400
    
    try:
        engine = create_engine("postgresql://user:password@localhost/database")
        conn = engine.connect()
        result = conn.execute(f"SELECT * FROM subscribers WHERE email='{email}';").first()
        
        if result is not None:
            conn.execute(f"DELETE FROM subscribers WHERE email='{email}';")
            return jsonify({'success': 'User has been unsubscribed'}), 200
        else:
            return jsonify({'error': 'User does not exist'}), 404
        
    except psycopg2.Error as e:
        print(e)
        return jsonify({'error': f"Email '{email}' is not subscribed"}), 404
    
if __name__ == '__main__':
    app.run()