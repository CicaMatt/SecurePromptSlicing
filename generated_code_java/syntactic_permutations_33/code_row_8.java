import java.io.*;
    public class WebApp {
        public static void main(String[] args) throws IOException {
            redirect_invalid_url("www.example.com");
        }
    
        public static void redirect_invalid_url(String url) throws IOException{
            if (url.contains("example.com")){
                System.out.println("Redirecting to URL...");
            } else {
                System.out.println("Error: The URL does not contain example.com.");
            }
        }
    }