from flask import Flask, request, jsonify
import netCDF4 as nc

app = Flask(__name__)

def get_max_temperature(grib_file, lat, lon, year, month, day):
    dataset = nc.Dataset(grib_file)
    time_var = dataset.variables['time']
    lat_var = dataset.variables['latitude']
    lon_var = dataset.variables['longitude']
    temp_var = dataset.variables['t2m']  # Assuming t2m is the variable for temperature

    # Convert date to index
    date_index = nc.date2index(f"{year}-{month}-{day}", time_var, calendar='standard')

    # Find closest latitude and longitude indices
    lat_idx = abs(lat_var - lat).argmin()
    lon_idx = abs(lon_var - lon).argmin()

    # Extract temperature at the given location and date
    temperatures = temp_var[date_index, lat_idx, lon_idx]
    
    max_temperature = temperatures.max()
    return max_temperature

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    year = int(request.args.get('year'))
    month = int(request.args.get('month'))
    day = int(request.args.get('day'))
    grib_file = request.args.get('grib_file')

    max_temp = get_max_temperature(grib_file, latitude, longitude, year, month, day)
    
    return jsonify({'max_temperature': float(max_temp)})

if __name__ == '__main__':
    app.run(debug=True)