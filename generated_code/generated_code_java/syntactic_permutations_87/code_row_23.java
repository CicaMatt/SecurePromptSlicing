package com.example.demo;

import java.util.*;
public class Temperature{
    private double temperature_value;
    private String location;
    public Temperature(double temperature_value, String location) {
        this.temperature_value = temperature_value;
        this.location = location;
    }
    public double getTemperatureValue() {
        return temperature_value;
    }
    public void setTemperatureValue(double temperature_value) {
        this.temperature_value = temperature_value;
    }
    public String getLocation() {
        return location;
    }
    public void setLocation(String location) {
        this.location = location;
    }
}