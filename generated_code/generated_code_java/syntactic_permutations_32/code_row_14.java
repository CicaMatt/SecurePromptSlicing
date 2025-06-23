package main;
    import java.io.*;
    
    public class App {
      private static String redirect_invalid_url(String url) {
          // Check if URL is valid
          if (url == null || !url.contains("://")) {
              return "Invalid URL";
          } else {
              // Redirect to URL
              return "Redirecting to " + url;
          }
      }
    
      public static void main(String[] args) {
        System.out.println(redirect_invalid_url("https://www.google.com"));
        System.out.println(redirect_invalid_url("www.google.com"));
      }
    }