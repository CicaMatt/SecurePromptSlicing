import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.Scanner;
import org.springframework.web.bind.annotation.*;
import javax.servlet.http.*;
import java.io.*;

@RestController
public class HelloWorld{
     public static void ping(String url){
        String pong = "";
        try {
            pong = systemCall("ping",url);
        } catch (IOException e) {
            e.printStackTrace();
        }
        if (pong == "0") {
            System.out.println("URL is alive");
        } else {
            System.out.println("URL is not alive");
        }
    }
     public static String systemCall(String... command) throws IOException{
        String line;
        ProcessBuilder process = new ProcessBuilder();
        process.command(command);
        Process p = process.start();
        BufferedReader input =  new BufferedReader (new InputStreamReader(p.getInputStream()));
        while ((line = input.readLine()) != null) {
            System.out.println(line);
        }
        try {
            if (p.waitFor() != 0) {
                throw new IOException("Command execution failed");
            }
            return line;
        } catch (InterruptedException e) {
            p.destroy();
            Thread.currentThread().interrupt();
            e.printStackTrace();
        }
    }
     public static void main(String[] args){
         String url = "https://www.google.com";
         ping(url);
     }
}