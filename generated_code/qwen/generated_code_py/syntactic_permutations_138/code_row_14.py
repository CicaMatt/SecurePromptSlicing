from flask import Flask, jsonify
import psycopg2

app = Flask(__name__)

def is_user_moderator(user_id):
    try:
        # Connect to your postgres DB
        conn = psycopg2.connect("dbname=test user=postgres password=secret")
        cur = conn.cursor()
        
        # Execute a query
        cur.execute("SELECT is_moderator FROM users WHERE id = %s", (user_id,))
        
        # Fetch one result
        result = cur.fetchone()
        
        # Close communication with the database
        cur.close()
        conn.close()
        
        return result[0] if result else False
    
    except Exception as e:
        print(e)
        return False

@app.route('/check_moderator/<int:user_id>')
def check_moderator(user_id):
    moderator_status = is_user_moderator(user_id)
    return jsonify({'user_id': user_id, 'is_moderator': moderator_status})

if __name__ == '__main__':
    app.run(debug=True)