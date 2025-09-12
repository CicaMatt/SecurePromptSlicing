from flask import Flask, request, jsonify
import netCDF4 as nc

app = Flask(__name__)

def get_max_temperature(latitude, longitude, year, month, day, grib_file):
    dataset = nc.Dataset(grib_file)
    time_var = dataset.variables['time']
    lat_var = dataset.variables['latitude'][:]
    lon_var = dataset.variables['longitude'][:]
    temp_var = dataset.variables['t2m'][:]

    # Convert date to index
    date_index = nc.date2index(f"{year}-{month:02d}-{day:02d}", time_var, calendar='standard')

    # Find nearest latitude and longitude indices
    lat_idx = (abs(lat_var - latitude)).argmin()
    lon_idx = (abs(lon_var - longitude)).argmin()

    # Extract temperature at the given location and date
    temp_data = temp_var[date_index, lat_idx, lon_idx]
    max_temp = temp_data.max()
    
    dataset.close()
    return max_temp

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    year = int(request.args.get('year'))
    month = int(request.args.get('month'))
    day = int(request.args.get('day'))
    grib_file = request.args.get('grib_file')

    max_temp = get_max_temperature(latitude, longitude, year, month, day, grib_file)
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)