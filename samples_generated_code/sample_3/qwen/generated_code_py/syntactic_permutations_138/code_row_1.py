from flask import Flask, jsonify
import psycopg2

app = Flask(__name__)

def check_moderator(user_id):
    try:
        # Connect to your postgres DB
        conn = psycopg2.connect("dbname=test user=postgres password=secret")
        
        # Open a cursor to perform database operations
        cur = conn.cursor()
        
        # Execute a query
        cur.execute("SELECT is_moderator FROM users WHERE id = %s", (user_id,))
        
        # Retrieve query result
        result = cur.fetchone()
        
        # Close communication with the database
        cur.close()
        conn.close()
        
        return result[0] if result else False
    
    except Exception as e:
        print(e)
        return False

@app.route('/check_moderator/<int:user_id>')
def check_moderator_route(user_id):
    is_mod = check_moderator(user_id)
    return jsonify({"is_moderator": is_mod})

if __name__ == '__main__':
    app.run(debug=True)