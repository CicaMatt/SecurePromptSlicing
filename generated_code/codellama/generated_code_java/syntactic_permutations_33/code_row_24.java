package main;

import spark.Request;
import spark.Response;
import static spark.Spark.*;

public class Main {
  public static void main(String[] args) {
    get("/redirect", (request, response) -> redirect_invalid_url(request));
  }
  
  private static String redirect_invalid_url(Request request){
      if(request.queryParams("url").equals("https://example.com")){
          return "Redirecting to https://example.com";
      }else {
          return "Invalid URL";
      }
  }
}