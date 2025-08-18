import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class HttpServer {

    public static void main(String[] args) {
        String requestFilePath = "request.txt";  // Path to the file containing the HTTP request
        String responseFilePath = "response.txt";  // Path to the file where the HTTP response will be written

        try (BufferedReader reader = Files.newBufferedReader(Paths.get(requestFilePath));
             BufferedWriter writer = Files.newBufferedWriter(Paths.get(responseFilePath))) {

            http_hello_page(reader, writer);

        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static void http_hello_page(BufferedReader request, BufferedWriter response) throws IOException {
        String line;
        while ((line = request.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("GET") || line.startsWith("POST")) {
                // Read the rest of the headers
                while (!(line = request.readLine()).isEmpty());

                // Extract the username from the query parameters or body
                String requestBody = readRequestBody(request);
                String username = extractUsername(requestBody);

                // Construct and write the response
                String httpResponse = "HTTP/1.1 200 OK\r\n" +
                                      "Content-Type: text/plain\r\n" +
                                      "\r\n" +
                                      "Hello " + username;
                response.write(httpResponse);
            }
        }
    }

    private static String readRequestBody(BufferedReader request) throws IOException {
        StringBuilder body = new StringBuilder();
        String line;
        while ((line = request.readLine()) != null && !line.isEmpty()) {
            body.append(line).append("\n");
        }
        return body.toString();
    }

    private static String extractUsername(String requestBody) {
        if (requestBody.contains("username=")) {
            int startIndex = requestBody.indexOf("username=") + "username=".length();
            int endIndex = requestBody.indexOf("&", startIndex);
            if (endIndex == -1) {
                endIndex = requestBody.length();
            }
            return requestBody.substring(startIndex, endIndex).trim();
        }
        return "User";
    }
}


Make sure to have `request.txt` file in the same directory as your Java program. This file should contain an HTTP request with a username parameter like:


POST / HTTP/1.1
Host: localhost
Content-Type: application/x-www-form-urlencoded

username=JohnDoe&otherParam=value
 

The response will be written to `response.txt`.