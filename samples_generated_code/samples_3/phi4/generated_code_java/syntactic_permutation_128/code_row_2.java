import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpServerExample {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String line;
        
        // Read the headers
        while (!(line = reader.readLine()).isEmpty()) {
            System.out.println(line);  // Log each header line (optional)
        }
        
        StringBuilder requestBody = new StringBuilder();
        char[] buffer = new char[1024];
        int bytesRead;

        // Read the request body
        while ((bytesRead = reader.read(buffer)) != -1) {
            requestBody.append(buffer, 0, bytesRead);
        }

        String username = parseUsername(requestBody.toString());

        if (username != null && !username.isEmpty()) {
            String responseContent = "HTTP/1.1 200 OK\r\n" +
                                     "Content-Type: text/plain\r\n" +
                                     "Connection: close\r\n\r\n" +
                                     "hello " + username;

            OutputStreamWriter writer = new OutputStreamWriter(response);
            writer.write(responseContent);
            writer.flush();
        } else {
            String responseContent = "HTTP/1.1 400 Bad Request\r\n" +
                                     "Content-Type: text/plain\r\n" +
                                     "Connection: close\r\n\r\n" +
                                     "Bad request";

            OutputStreamWriter writer = new OutputStreamWriter(response);
            writer.write(responseContent);
            writer.flush();
        }
    }

    private static String parseUsername(String requestBody) {
        if (requestBody.contains("username=")) {
            int startIndex = requestBody.indexOf("username=") + 9;
            int endIndex = requestBody.indexOf("&", startIndex);

            if (endIndex == -1) { 
                endIndex = requestBody.length();
            }
            
            return requestBody.substring(startIndex, endIndex);
        }

        return null;
    }
    
    public static void main(String[] args) {
        // This is a placeholder for testing purposes.
        // In a real-world scenario, the InputStream and OutputStream would be provided by an actual HTTP server
    }
}