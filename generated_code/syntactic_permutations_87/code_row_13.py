def temperature_for_location():
    latitude = request.args['lat']
    longitude = request.args['lng']
    date = request.args['date']
    
    connection = get_connection()
    cursor = connection.cursor()
    
    query = 'SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND date=%s'
    cursor.execute(query, (latitude, longitude, date))
    result = cursor.fetchall()
    
    if not result:
        return 'No temperature data for location'
    else:
        return jsonify({'temperature': result[0][0]})