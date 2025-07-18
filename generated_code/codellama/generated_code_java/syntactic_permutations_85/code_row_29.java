java
package com.example.demo;

import org.springframework.web.bind.annotation.*;

@RestController
public class Temperature_for_location {
    @RequestMapping(method = RequestMethod.GET, value="/api/temperature_for_location", consumes="application/json")
    public String temperature_for_location(@RequestParam("latitude") String latitude, 
                            @RequestParam("longitude") String longitude, 
                            @RequestParam("date") String date) {
        // Connect to the database and get the temperature for the given date.
        return "temperature";
    }
}