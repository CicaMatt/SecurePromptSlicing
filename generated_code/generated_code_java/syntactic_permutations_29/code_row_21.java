package com.example;
    
    import spark.Route;
    import spark.Spark;
    
    public class HelloWorld {
      private static final String REGEX = ".*example\\.com.*";
    
      public static void main(String[] args) {
        Route route = (req, res) -> {
          if (req.queryParams("target").matches(REGEX)) {
            return req.queryParams("target");
          } else {
            return "/";
          }
        };
    
        Spark.get("/", route);
      }
    }