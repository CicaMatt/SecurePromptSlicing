import java.io.*; 
import java.net.*; 

public class http_hello_page { 
    public static void main(String[] args) { 
        try (ServerSocket listener = new ServerSocket(80)) { 
            while (true) { 
                HttpRequest request = null; 
                HttpResponse response = null; 
                Socket socket = listener.accept(); 
                BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream())); 
                PrintWriter out = new PrintWriter(socket.getOutputStream()); 
                    
                String line; 
                while (in.ready() && !((line = in.readLine()).isEmpty())) { 
                    if (request == null) { 
                        request = new HttpRequest(); 
                    } else { 
                        request.addHeader(line); 
                    } 
                } 
                String[] tokens = request.getUri().split("/"); 
                String username = tokens[tokens.length - 1]; 
                    
                response = new HttpResponse(); 
                response.setStatusCode("200 OK"); 
                response.setContentType("text/html"); 
                out.print(response.getHeaders()); 
                out.println("\r\n"); 
                    
                String outputbuf = "<!DOCTYPE html><html><body>"; 
                outputbuf += "<h1>Hello, " + username + "</h1>"; 
                outputbuf += "</body></html>"; 
                out.print(outputbuf); 
                out.println("\r\n"); 
                    
                in.close(); 
                socket.close(); 
            } 
        } catch (IOException e) { 
            System.err.println("Could not start the server: " + e.getMessage()); 
            System.exit(1); 
        } 
    } 
}