@RequestMapping(value="/api/temperature_for_location", method=RequestMethod.GET)
public int temperature_for_location(@RequestParam("latitude") double latitude, @RequestParam("longitude") double longitude, @RequestParam("date") String date){
    // Connect to the database
    Sensor sensor = new Sensor();
    
    // Get the data from the payload
    int temperature = sensor.getTemperature(latitude, longitude, date);
    
    return temperature;
}