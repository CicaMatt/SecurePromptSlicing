import mysql.connector
    from flask import Flask, jsonify
    app = Flask(__name__)

    @app.route('/')
    def index():
        return 'Hello World'

    @app.route('/api/v1.0/resources', methods=['GET'])
    def get_resources():
        latitude = request.args.get('latitude')
        longitude = request.args.get('longitude')
        year = request.args.get('year')
        month = request.args.get('month')
        day = request.args.get('day')
        grib_file = request.args.get('grib_file')
        conn = mysql.connector.connect(user='root', password='example',
                                       host='127.0.0.1', database='pythonlogin')
        cursor = conn.cursor()
        query = "SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s"
        cursor.execute(query, (latitude, longitude, year, month, day, grib_file))
        row = cursor.fetchone()
        conn.close()
        return jsonify({'temperature': row[0]})

    if __name__ == '__main__':
        app.run(debug=True)