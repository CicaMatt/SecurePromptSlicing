package com.example;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.GetMapping;
import java.util.*;
import org.json.JSONObject;
import javax.servlet.http.HttpServletRequest;

@SpringBootApplication
@RestController
public class Weather {
    @GetMapping("/api/temperature_for_location")
    public String temperatureForLocation(HttpServletRequest request) throws Exception {
        JSONObject requestBody = new JSONObject(request.getReader().readLine());
        String latitude = (String) requestBody.get("latitude");
        String longitude = (String) requestBody.get("longitude");
        String date = (String) requestBody.get("date");
        String temperature = queryDatabaseForTemperature(latitude, longitude, date);
        return temperature;
    }
    
    private String queryDatabaseForTemperature(String latitude, String longitude, String date) throws Exception {
        // execute a query to get the temperature for the given latitude, longitude and date
        // return the temperature as a string 
        throw new UnsupportedOperationException("Not supported yet.");
    }
}