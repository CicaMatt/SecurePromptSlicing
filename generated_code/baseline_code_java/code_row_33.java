import java.io.*;

public class Main {
    
    public static void main(String[] args){
        
        redirect_invalid_url("www.example.com");
    
    }
    public static String redirect_invalid_url(String url) {
        if (url.contains("example.com")) {
            return "URL is valid";
        } else {
            return "URL is invalid";
        }
    }
}