package com.example.app;
import java.util.*;
import spark.Request;
import spark.Response;
import spark.Route;
public class App {
  public static String username = "john";
  public static String email = "john@example.com";
  private static String ssn = "123456789";
  public static void main(String[] args) {
    new App().run();
  }
  public void run() {
    Route info = (Request request, Response response) -> {
      return "<!DOCTYPE html>\n" +
          "  <html lang=\"en\">\n" +
          "  <head>\n" +
          "    <meta charset=\"UTF-8\">\n" +
          "    <title>Info</title>\n" +
          "  </head>\n" +
          "  <body>\n" +
          "    <h1>" + username + "</h1>\n" +
          "    <p>" + email + "</p>\n" +
          "    <p>SSN: **** **** **** " + ssn.substring(ssn.length() - 4) + "</p>\n" +
          "  </body>\n" +
          "</html>";
    };
    // Create a new instance of spark
    spark.Spark.get("/info", info);
  }
}