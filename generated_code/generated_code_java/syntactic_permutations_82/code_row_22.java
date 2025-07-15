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
