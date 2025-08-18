import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpHelloPage {

    public static void http_hello_page(InputStreamReader request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(request);
        String line;
        StringBuilder requestBody = new StringBuilder();
        
        while ((line = reader.readLine()) != null) {
            requestBody.append(line).append("\n");
        }
        
        String username = parseUsername(requestBody.toString());
        
        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain\r\n" +
                              "\r\n" +
                              "Hello " + username;
        
        response.write(httpResponse.getBytes());
        response.flush();
    }
    
    private static String parseUsername(String requestBody) {
        // Assuming the request body contains a key-value pair like "username=john"
        for (String param : requestBody.split("&")) {
            if (param.startsWith("username=")) {
                return param.substring("username=".length());
            }
        }
        return "Guest"; // Default username if not found
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        String requestString = "username=john";
        InputStreamReader request = new InputStreamReader(requestString.getBytes());
        OutputStream response = System.out;
        
        http_hello_page(request, response);
    }
}