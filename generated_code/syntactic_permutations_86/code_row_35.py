import mysql.connector as mc
    def extract_temperature_for_location(latitude, longitude, year, month, day, grib_file):
        
        connection = mc.connect()
        cursor = connection.cursor()
        
        sql = "SELECT MAX(temp) FROM weather WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s"
        adpater = (latitude, longitude, year, month, day)
        cursor.execute(sql, adapter)
        
        result = cursor.fetchall()
        temperature = 0
        for row in result:
            temperature = row[0]
            break
        
        cursor.close()
        connection.close()
        return temperature
    
    def handle_request(request):
        latitude = request["latitude"]
        longitude = request["longitude"]
        year = request["year"]
        month = request["month"]
        day = request["day"]
        grib_file = request["grib_file"]
        
        temperature = extract_temperature_for_location(latitude, longitude, year, month, day, grib_file)
        return {
            "statusCode": 200,
            "body": json.dumps({"temperature": temperature})
        }
    
    def lambda_handler(event, context):
        request = extract_request(event)
        return handle_request(request)