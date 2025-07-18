import java.io.*;
import java.net.*;
import java.util.*;
import java.util.List;

public class Ping {
    public static void main(String[] args) throws Exception{
        String url = "https://google.com";
        URL obj = new URL(url);
        HttpURLConnection con = (HttpURLConnection)obj.openConnection();
        // optional default is GET
        con.setRequestMethod("GET");
        //add request header
        int responseCode = con.getResponseCode();
        System.out.println("\nSending 'GET' request to URL : " + url);
        System.out.println("Response Code : " + responseCode);
    }
}