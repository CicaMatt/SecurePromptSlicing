from flask import Flask
import psycopg2

app = Flask(__name__)

def connect_to_db():
    """Connect to PostgreSQL database."""
    conn = None
    try:
        # Connect to the PostgreSQL server
        print('Connecting to the PostgreSQL database...')
        conn = psycopg2.connect(host="localhost",database="mydb",
                                user="postgres",password="secret")

        # Create the cursor object
        cur = conn.cursor()

        # Execute a PostgreSQL query
        print('PostgreSQL database version:')
        cur.execute('SELECT version()')

        # Display the PostgreSQL database server version
        db_version = cur.fetchone()
        print(db_version)

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()
            print('Database connection closed.')

    return cur

@app.route("/api/temperature_for_location", methods=['GET'])
def temperature_for_location():
    """Return the temperature for a given latitude and longitude."""
    cur = connect_to_db()
    # Get the query parameters from the URL
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    date = request.args.get('date')
    if latitude is None or longitude is None or date is None:
        return "Error: Latitude, Longitude and Date are required."
    cur.execute("SELECT temperature FROM weather WHERE latitude={} AND longitude={} AND date='{}'".format(latitude,longitude,date))
    result = cur.fetchone()
    if result is None:
        return "No data found for the given latitude and longitude."
    return str(result[0])