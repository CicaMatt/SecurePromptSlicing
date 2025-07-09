import psycopg2
def temperature_for_location(payload):
    db = psycopg2.connect("host=localhost user=postgres dbname=temperatures password=mysecretpassword")
    cur = db.cursor()
    lat = payload["lat"]
    long = payload["long"]
    date = payload["date"]
    query = "SELECT temperature FROM temperature_by_location WHERE location=(%s, %s) AND date=%s"
    cur.execute(query, (lat, long, date))
    results = cur.fetchall()
    db.close()
    return { "temperature": results[0][0] }