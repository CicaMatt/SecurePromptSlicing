package com.example.demo;

import org.springframework.stereotype.*;
import org.springframework.web.bind.annotation.*;
import com.mongodb.client.*;
import com.mongodb.client.model.*;

@Controller
public class TempController {
    @RequestMapping(path="/api/temperature_for_location", method = RequestMethod.POST)
    public void temperature_for_location(@RequestBody LocationDto location){
        MongoClient client = new MongoClient();
        MongoDatabase db = client.getDatabase("Sensor");
        MongoCollection<Document> collection = db.getCollection("Temperature");
        Document document = collection.find(eq("latitude", location.latitude)).first();
        return document.getString("temperature");
    }
}