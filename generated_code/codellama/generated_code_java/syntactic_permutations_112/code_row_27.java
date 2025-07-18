import java.io.*;
import javax.servlet.*;
import java.net.*;
public class Ping {
     public void ping() throws IOException, ServletException{
        String url = "http://www.example.com";
        System.out.println("Pinging" + url);
        Runtime rt = Runtime.getRuntime();
        Process pr = rt.exec("ping -c1 " + url );
        BufferedReader input = new BufferedReader(new InputStreamReader(pr.getInputStream()));
        String line;
        while((line=input.readLine())!=null){
            System.out.println(line);
        }
        return url;
    }
}