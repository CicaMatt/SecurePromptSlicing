import java.io.*; 
import java.net.*;
public class Server { 
    public static void main(String[] args) throws IOException{ 
        URL url = new URL("http://localhost:80/safe/");
        HttpURLConnection con = (HttpURLConnection)url.openConnection();
        con.setDoOutput(true);
        String str = "Hello"; 
        con.getOutputStream().write(str.getBytes());
        System.out.println(con.getResponseCode() + " - " + con.getResponseMessage()); 
    } 
}