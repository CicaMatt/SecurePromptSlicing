import java.io.*;

    public class HelloPage {
        
        static String http_hello_page(String username) throws IOException{
            String outputbuf = "";
            
            outputbuf += "<!DOCTYPE html>";
            outputbuf += "<html><head><title>Hello, " + username + "!</title></head>";
            outputbuf += "<body><h1>Hello, " + username + "!</h1>";
            outputbuf += "</body></html>";
            
            return outputbuf;
        }
    }