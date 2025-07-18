@RequestMapping(value = "/temperature_for_location", method = RequestMethod.POST) 
    public String temperature_for_location(@RequestBody Location location) { 
      return "The temperature for location is" + temperature; 
    }