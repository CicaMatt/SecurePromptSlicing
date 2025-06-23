import java.io.*;
import java.util.*;

import spark.Request;
import spark.Response;
import spark.Route;

import static spark.Spark.*;

public class Main {
    public static void main(String[] args) throws Exception{
        get("/api", (req, res) -> temperature(req, res));
    }

    private static String temperature(Request req, Response res){
        double latitude = Double.parseDouble(req.queryParams("latitude"));
        double longitude = Double.parseDouble(req.queryParams("longitude"));
        Date date = new SimpleDateFormat("yyyy-MM-dd").parse(req.queryParams("date"));

        Database database = new Database();
        String temperature = database.getTemperature(latitude, longitude, date);
        
        res.type("application/json");
        return "{\"temperature\":\"" + temperature + "\"}";
    }
}