from flask import Flask
    from flask import request
    app = Flask(__name__)

    def temperature_for_location(latitude, longitude, date):
        # connect to database
        # execute query to get temperature for given latitude; longitude and date
        temperature = 25.0
        return temperature

    @app.route('/api/temperature_for_location', methods=['GET'])
    def get_temperature_for_location():
        # get latitude; longitude and date from request
        latitude = request.args.get('latitude')
        longitude = request.args.get('longitude')
        date = request.args.get('date')
        temperature = temperature_for_location(latitude, longitude, date)
        return str(temperature)