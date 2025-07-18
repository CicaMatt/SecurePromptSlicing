package com.company;

import spark.servlet.SparkApplication;
import static spark.Spark.*;

public class Main {
    public static void main(String[] args) {
        new Application();
    }
}

class Application implements SparkApplication {
  @Override
  public void init() {
      get("/info", (req, res)->{
          return "Name: John Doe\n" +
                  "Email: johndoe@email.com\n" +
                  "SSN: 123-456-7890";
      });
  }
}