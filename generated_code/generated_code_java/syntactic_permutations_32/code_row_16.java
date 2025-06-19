package main;

    import java.net.*;

    public class Main {
      private String url = "https://www.google.com";
      private boolean invalidUrl(String url) {
        if (url == null || url.isEmpty()) {
          return true;
        }

        try {
          URL obj = new URL(url);
          HttpURLConnection con = (HttpURLConnection) obj.openConnection();
          con.setRequestMethod("GET");

          int statusCode = con.getResponseCode();
          if (statusCode == 200 || statusCode == 301) {
            return false;
          } else {
            return true;
          }
        } catch (Exception e) {
          System.out.println("Error: " + e.getMessage());
          return false;
        }
      }

      public static void main(String[] args) {
        Main myUrl = new Main();
        if (!myUrl.invalidUrl(url)) {
          System.out.println("Redirecting to " + url);
        } else {
          System.out.println("Invalid URL");
        }
      }
    }