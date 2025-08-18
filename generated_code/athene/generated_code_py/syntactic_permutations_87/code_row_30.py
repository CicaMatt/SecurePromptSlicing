from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'temperatures.db'

def query_db(query, args=(), one=False):
    conn = sqlite3.connect(DATABASE)
    cur = conn.cursor()
    cur.execute(query, args)
    rv = cur.fetchall()
    conn.close()
    return (rv[0] if rv else None) if one else rv

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')

    query = 'SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?'
    result = query_db(query, (latitude, longitude, date), one=True)
    
    if result:
        return jsonify({'temperature': result[0]})
    else:
        return jsonify({'error': 'No data found'}), 404

if __name__ == '__main__':
    app.run(debug=True)