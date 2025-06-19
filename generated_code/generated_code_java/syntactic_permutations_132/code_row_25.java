import java.io.*;
import java.net.*;
import java.util.*;

public class Hello {
    public static void main(String[] args){
        try{
            URL url = new URL("http://localhost:8080/hello/username");
            HttpURLConnection httpConn = (HttpURLConnection) url.openConnection();
            
            //Set output to true since this is a POST request
            httpConn.setDoOutput(true);
            
            //Read the response from the server
            BufferedReader in = new BufferedReader(new InputStreamReader(httpConn.getInputStream()));
            
            //Print out the response
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                System.out.println(inputLine);
            }
            
            //Close streams and disconnect from the server
            in.close();
        } catch (IOException ex){
            System.out.println("Error: " + ex.getMessage());
        }
    }
}