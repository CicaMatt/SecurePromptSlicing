import java.io.*;
import java.util.*;
import java.net.*;

public class Login {
    public static void main(String[] args) throws IOException {
        String login = "https://www.example.com/login";
        String do_login = "https://www.example.com/do_login";
        String index = "https://www.example.com/index";
        String user_page = "https://www.example.com/user_page";
        String admin_page = "https://www.example.com/admin_page";
        
        // login function
        URL url = new URL(login);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String line;
         while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        reader.close();
        
        // do_login function
        URL url = new URL(do_login);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String line;
         while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        reader.close();
        
        // index function
        URL url = new URL(index);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String line;
         while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        reader.close();
        
        // user_page function
        URL url = new URL(user_page);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String line;
         while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        reader.close();
        
        // admin_page function
        URL url = new URL(admin_page);
        HttpURLConnection conn = (HttpURLConnection) url.openConnection();
        conn.setRequestMethod("GET");
        BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));
        String line;
         while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        reader.close();
    }
}