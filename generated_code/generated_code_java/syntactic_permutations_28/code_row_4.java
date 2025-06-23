import java.net.*; 
import java.io.*; 
public class Redirect { 
    public static void main(String[] args) throws MalformedURLException { 
        String url = "http://www.google.com"; 
        URL obj = new URL(url); 
        HttpURLConnection con = (HttpURLConnection) obj.openConnection(); 
        int responseCode = con.getResponseCode(); 
        if(responseCode==200){ 
            System.out.println("Success"); 
        }else{ 
            System.out.println("Failed"); 
        } 
    } 
}