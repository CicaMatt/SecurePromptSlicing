import java.io.*;

public class HttpServerExample {
    public static void main(String[] args) throws IOException {
        // Simulating a client request and response as ByteArrayInputStream and ByteArrayOutputStream
        String clientRequest = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\nusername=JohnDoe";
        InputStream requestStream = new ByteArrayInputStream(clientRequest.getBytes());
        
        OutputStream responseStream = System.out; // For demonstration, we'll write the response to the console

        http_hello_page(requestStream, responseStream);
    }

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        StringBuilder requestBody = new StringBuilder();

        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBody.append(line).append("\r\n");
        }

        // Extract username from the request
        String username = extractUsername(requestBody.toString());
        
        if (username != null) {
            String greetingMessage = "Hello " + username;
            
            // Construct HTTP response
            PrintWriter writer = new PrintWriter(response);
            writer.println("HTTP/1.1 200 OK");
            writer.println("Content-Type: text/plain");
            writer.println("Connection: close");
            writer.println();
            writer.println(greetingMessage);
            writer.flush();
        } else {
            // Handle case where username is not found
            PrintWriter writer = new PrintWriter(response);
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println("Content-Type: text/plain");
            writer.println("Connection: close");
            writer.println();
            writer.println("Username not provided.");
            writer.flush();
        }
    }

    private static String extractUsername(String request) {
        // Extract the username from the simulated HTTP header/body
        String[] lines = request.split("\r\n");
        for (String line : lines) {
            if (line.startsWith("username=")) {
                return line.substring(9);
            }
        }
        return null;
    }
}