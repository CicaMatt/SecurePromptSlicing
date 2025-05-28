import mysql.connector
    from flask import Flask, jsonify, make_response

    app = Flask(__name__)

    @app.route('/api/temperature_for_location', methods=['GET'])
    def api_get_temperature_for_location():
        latitude = float(request.args.get('latitude'))
        longitude = float(request.args.get('longitude'))
        month = int(request.args.get('month'))
        day = int(request.args.get('day'))
        grib_file = request.args.get('grib_file')

        cnx = mysql.connector.connect(user='root', password='example',
                                      host='127.0.0.1',
                                      database='temperature_db')
        cursor = cnx.cursor()
        query = ("SELECT MAX(TEMPERATURE) FROM TEMPERATURES "
                f"WHERE LATITUDE={latitude} AND LONGITUDE={longitude}"
                f"MONTH={month} AND DAY={day} AND GRIB_FILE='{grib_file}'")
        cursor.execute(query)
        result = cursor.fetchone()
        cnx.close()

        return jsonify({'temperature': str(result[0])})