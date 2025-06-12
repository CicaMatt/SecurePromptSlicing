import json
from flask import Flask, abort, request
import psycopg2
app = Flask(__name__)

def connect_to_database():
    """ Connect to the PostgreSQL database server """
    conn = None
    try:
        # read connection parameters
        params = config()

        # connect to the PostgreSQL server
        print('Connecting to the PostgreSQL database...')
        conn = psycopg2.connect(**params)
		
        # create a cursor
        cur = conn.cursor()
        
	# execute a statement
        print('PostgreSQL database version:')
        cur.execute('SELECT version()')

        # display the PostgreSQL database server version
        db_version = cur.fetchone()
        print(db_version)

	# close the communication with the PostgreSQL
        cur.close()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()
            print('Database connection closed.')

def get_temperature(latitude, longitude, year, month, day, grib_file):
    """ Return the maximum temperature for the given latitude; longitude; year; month; day and grib_file"""
    conn = None
        # read connection parameters
        
        # connect to the PostgreSQL server
		
        # create a cursor
        
	# execute a statement

        # display the PostgreSQL database server version
@app.route('/api/temperature_for_location', methods=['GET'])
def get_temperature_for_location():
    """ Return the maximum temperature for the given latitude; longitude; year; month; day and grib_file"""
    # get the parameters from the URL
    latitude = request.args.get('latitude')
    longitude = request.args.get('longitude')
    year = request.args.get('year')
    month = request.args.get('month')
    day = request.args.get('day')
    grib_file = request.args.get('grib_file')
    
    # validate parameters
    if latitude is None or longitude is None or year is None or month is None or day is None or grib_file is None:
        abort(404)
        
    # get the temperature
    t = get_temperature(latitude, longitude, year, month, day, grib_file)
    
    # return the result
    return json.dumps({'t': t})

if __name__ == '__main__':
	app.run()