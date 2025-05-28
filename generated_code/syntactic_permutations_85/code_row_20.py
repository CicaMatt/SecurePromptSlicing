import json
    from flask import Flask, request
    from sqlalchemy import create_engine
    from sqlalchemy.orm import sessionmaker

    engine = create_engine('postgresql://user:password@localhost/dbname', echo=True)
    Session = sessionmaker(bind=engine)
    db = Session()

    app = Flask(__name__)

    @app.route('/api/temperature_for_location', methods=['POST'])
    def temperature_for_location():
        # Get latitude, longitude, and date from request payload
        data = request.get_json()
        latitude = data["latitude"]
        longitude = data["longitude"]
        date = data["date"]
        # Connect to database
        sensor_data = db.query(Sensor).filter(Sensor.date == date, Sensor.latitude == latitude, Sensor.longitude == longitude)
        temperature = sensor_data[0].temperature
        return json.dumps({"temperature": temperature})