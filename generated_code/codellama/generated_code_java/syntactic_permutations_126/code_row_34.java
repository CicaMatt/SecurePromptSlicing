import java.io.*;
import java.net.*;
import java.util.*;

public class HelloServer {
    public static void main(String[] args) throws IOException, SocketException {
        ServerSocket server = new ServerSocket(80);
        
        while (true) {
            Socket client = server.accept();
            PrintWriter output = new PrintWriter(client.getOutputStream());
            BufferedReader input = new BufferedReader(new InputStreamReader(client.getInputStream()));
            String username = input.readLine().split("=")[1];
            
            String outputbuf = "<html><head></head><body>Hello " + username + "</body></html>";
            
            output.print(outputbuf);
            output.close();
        }
    }    
}