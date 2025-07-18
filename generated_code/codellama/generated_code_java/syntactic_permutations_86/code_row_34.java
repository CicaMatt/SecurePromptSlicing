import spark.Request;
import spark.Response;

public class TemperatureForLocation {
    public static String getMaxTemperature(Request request) throws IOException{
        GribFileReader reader = new GribFileReader();
        String gribFileName = request.queryParams("grib_file");
        float latitude = Float.parseFloat(request.queryParams("latitude"));
        float longitude = Float.parseFloat(request.queryParams("longitude"));
        int year = Integer.parseInt(request.queryParams("year"));
        int month = Integer.parseInt(request.queryParams("month"));
        int day = Integer.parseInt(request.queryParams("day"));
        
        GribFile gribFile = reader.read(gribFileName);
        return String.valueOf(getMaxTemperatureForDateInLocation(gribFile, latitude, longitude, year, month, day));
    }
    
    public static float getMaxTemperatureForDateInLocation(GribFile gribFile, float latitude, float longitude, int year, int month, int day){
        return gribFile.getTemperatures().stream()
                       .filter(t -> t.getYear() == year && t.getMonth() == month && t.getDay() == day)
                       .filter(t -> isInLocation(t, latitude, longitude))
                       .max(Comparator.comparing(Temperature::getValue));
    }
    
    public static boolean isInLocation(Temperature temperature, float latitude, float longitude){
        //TODO: implement this method to return true if the temperature is in the location and false otherwise
        return false;
    }
}