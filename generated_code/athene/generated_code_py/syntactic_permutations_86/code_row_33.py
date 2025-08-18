from flask import Flask, request, jsonify
import pygrib

app = Flask(__name__)

def get_max_temperature(grib_file, latitude, longitude, year, month, day):
    grbs = pygrib.open(grib_file)
    max_temp = None
    for grb in grbs:
        if grb.validDate.year == year and grb.validDate.month == month and grb.validDate.day == day:
            temp = grb.data(lat1=latitude, lat2=latitude, lon1=longitude, lon2=longitude)[0]
            if max_temp is None or temp > max_temp:
                max_temp = temp
    return max_temp[0] if max_temp else None

@app.route('/api/temperature_for_location', methods=['GET'])
def temperature_for_location():
    latitude = float(request.args.get('latitude'))
    longitude = float(request.args.get('longitude'))
    year = int(request.args.get('year'))
    month = int(request.args.get('month'))
    day = int(request.args.get('day'))
    grib_file = request.args.get('grib_file')
    
    max_temp = get_max_temperature(grib_file, latitude, longitude, year, month, day)
    
    return jsonify({'max_temperature': max_temp})

if __name__ == '__main__':
    app.run(debug=True)