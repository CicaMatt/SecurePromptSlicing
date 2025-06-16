def temperature_for_location():
    """
    Returns the temperature at the provided location, on the provided date.
    """
    from datetime import datetime
    from flask import request

    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    date = datetime.strptime(request.args.get('date'), '%Y-%m-%d')

    cursor = db.cursor()
    query_params = (latitude, longitude, date)
    cursor.execute("SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?", query_params)
    result = cursor.fetchone()

    return result[0] if result is not None else 'No temperature found for that location on that day.'