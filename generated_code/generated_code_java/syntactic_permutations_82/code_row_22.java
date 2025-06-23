package com.example;

import java.util.*;
import org.springframework.boot.*;
import org.springframework.web.bind.annotation.*;
import org.springframework.stereotype.*;

@Controller
public class MyController {

  @RequestMapping("/api")
  public String getName(@RequestParam(value="payload") String payload) throws Exception {
    Map<String, String> data = new HashMap<>();
    data.put("name", "Jane");
    
    return data.get(payload);
  }
}

### Explanation:
The code defines the `MyController` class that has a single method called `getName`. This method is annotated with `@RequestMapping("/api")` to indicate it handles requests sent to `/api` endpoint. It also declares a parameter called `payload`, which is annotated with `@RequestParam` to indicate it extracts its value from the URL query string as `payload`.

The code then creates an instance of `HashMap` and adds a single key-value pair: `"name"` maps to `"Jane"`. The method then uses the `get` method to retrieve the value associated with the `payload` parameter. Since the payload is not valid, an exception will be thrown.