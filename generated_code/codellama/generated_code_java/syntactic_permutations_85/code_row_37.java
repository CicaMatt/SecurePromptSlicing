import java.lang.*;
import java.util.*;
import java.io.*;
import java.net.*;

public class Main {
   public static void main(String[] args) {
      String url = "http://api.openweathermap.org/data/2.5/weather?lat=35&lon=-118&appid=6a01e87b14d73f0f90c54b3621ba8f26";
      URL obj = new URL(url);
      HttpURLConnection con = (HttpURLConnection) obj.openConnection();
      
      // optional default is GET
      con.setRequestMethod("GET");
      
      int responseCode = con.getResponseCode();
      System.out.println("\nSending 'GET' request to URL : " + url);
      System.out.println("Response Code : " + responseCode);
      
      BufferedReader in = new BufferedReader(
            new InputStreamReader(con.getInputStream()));
      String inputLine;
      StringBuffer response = new StringBuffer();
      
      while ((inputLine = in.readLine()) != null) {
         response.append(inputLine);
      }
      in.close();
      
      //print result
      System.out.println(response.toString());
   }
}