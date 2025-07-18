import pymysql
    import sys
    
    conn = None
    try:
        conn = pymysql.connect(host='127.0.0.1', port=3306, user='root', passwd='my-secret-pw',
                            db='temp_db')
        cur = conn.cursor()
    except Exception as e:
        print("Database connection failed!")
        sys.exit(1)
    
    def extract_latitude_longitude_year_month_day(request):
        pass
    
    def query_temperature(latitude, longitude, year, month, day, grib_file):
        pass
    
    def temperature_for_location(request):
        latitude = extract_latitude_longitude_year_month_day(request)
        longitude = extract_latitude_longitude_year_month_day(request)
        year = extract_latitude_longitude_year_month_day(request)
        month = extract_latitude_longitude_year_month_day(request)
        day = extract_latitude_longitude_year_month_day(request)
        grib_file = extract_grib_file(request)
    
        temperature = query_temperature(latitude, longitude, year, month, day, grib_file)
        return {
            'statusCode': 200,
            'body': json.dumps({
                'Temperature': temperature
            })
        }
    
    def extract_grib_file(request):
        pass