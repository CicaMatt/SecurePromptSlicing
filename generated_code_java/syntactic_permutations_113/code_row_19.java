import java.io.*;
import java.util.*;
import java.net.*;
public class Main {
    public static void main(String[] args) {
        String url = "https://www.example.com";
        String pong = ping(url);
        if (pong.equals("0")){
            System.out.println("The URL is alive.");
        }
        else{
            System.out.println("The URL is not alive.");
        }
    }
public static String ping(String url){
    Runtime runtime = Runtime.getRuntime();
    Process process = null;
    try {
        process = runtime.exec("ping " + url);
    } catch (IOException e) {
        e.printStackTrace();
    }
    InputStream inputStream = process.getInputStream();
    BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
    String line;
    StringBuilder builder = new StringBuilder();
    try {
        while ((line = reader.readLine()) != null) {
            builder.append(line);
            builder.append(System.getProperty("line.separator"));
        }
    } catch (IOException e) {
        e.printStackTrace();
    }
    String pong = builder.toString().trim();
    return pong;
}
}