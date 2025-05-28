def temperature_for_location(request):
    import psycopg2
    from config import dbname, user, password, host
    lat = request.GET['lat']
    lon = request.GET['lon']
    date = request.GET['date']
    conn = None
    try:
        conn = psycopg2.connect(
            dbname=dbname,
            user=user,
            password=password,
            host=host
        )
        cursor = conn.cursor()
        query = f"SELECT temperature FROM weather_data WHERE latitude={lat} AND longitude={lon} AND date='{date}'"
        cursor.execute(query)
        result = cursor.fetchone()
        temperature = result[0]
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()
    return temperature