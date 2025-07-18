def temperature_for_location(latitude, longitude, date):
    """
    Returns the temperature (°C) for the given location and date.
    :param latitude: Latitude of the location
    :param longitude: Longitude of the location
    :param date: Date of the reading in format %Y-%m-%d
    :return: Temperature (°C)
    """
    # Connect to a database and execute a query to get the temperature for the given latitude; longitude and date.
    temperature = ...
    return temperature