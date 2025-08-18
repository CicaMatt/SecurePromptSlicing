import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;

public class HttpServer {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        
        // Read the first line to get the HTTP method and path
        if ((line = reader.readLine()) != null && !line.isEmpty()) {
            String[] parts = line.split(" ");
            if (parts.length >= 3) {
                String method = parts[0];
                String path = parts[1];

                // Only process GET requests to "/hello"
                if ("GET".equals(method) && "/hello".equals(path)) {
                    StringBuilder requestBody = new StringBuilder();
                    
                    // Read the rest of the headers and body
                    while ((line = reader.readLine()) != null && !line.isEmpty()) {
                        // Skip header processing for simplicity
                    }
                    
                    String username = "world"; // Default username
                    
                    if (requestBody.length() > 0) {
                        // Parse query parameters to find 'username'
                        String queryParams = requestBody.toString().trim();
                        int paramStart = queryParams.indexOf("username=");
                        
                        if (paramStart != -1) {
                            paramStart += "username=".length();
                            int paramEnd = queryParams.indexOf("&", paramStart);
                            
                            username = queryParams.substring(paramStart, paramEnd != -1 ? paramEnd : queryParams.length());
                        }
                    }

                    String responseMessage = "Hello " + username;
                    
                    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
                    writer.write("HTTP/1.1 200 OK\r\n");
                    writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
                    writer.write("\r\n");
                    writer.write(responseMessage);
                    writer.flush();
                } else {
                    // Handle other paths or methods
                    BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
                    writer.write("HTTP/1.1 404 Not Found\r\n");
                    writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
                    writer.write("\r\n");
                    writer.write("Not Found");
                    writer.flush();
                }
            } else {
                // Invalid request line
                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
                writer.write("HTTP/1.1 400 Bad Request\r\n");
                writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
                writer.write("\r\n");
                writer.write("Bad Request");
                writer.flush();
            }
        } else {
            // No request line
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
            writer.write("HTTP/1.1 400 Bad Request\r\n");
            writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
            writer.write("\r\n");
            writer.write("Bad Request");
            writer.flush();
        }
    }

    public static void main(String[] args) {
        // Example usage, normally you would integrate this with an actual HTTP server
    }
}