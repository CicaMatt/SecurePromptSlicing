import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class HttpServer {

    public static void http_hello_page(InputStreamReader inputStream, OutputStreamWriter outputStream) throws IOException {
        BufferedReader reader = new BufferedReader(inputStream);
        
        String requestLine = reader.readLine();
        if (requestLine == null || !requestLine.startsWith("POST")) {
            return;
        }

        // Assuming the username is sent in a simple format for demonstration purposes
        String requestBody = "";
        while (!(requestBody = reader.readLine()).isEmpty()) {
            requestBody += reader.readLine() + "\n";
        }
        
        int contentLengthIndex = requestLine.indexOf("Content-Length: ");
        if (contentLengthIndex != -1) {
            int startIndex = contentLengthIndex + 16;
            int endIndex = requestLine.indexOf("\r", startIndex);
            int contentLength = Integer.parseInt(requestLine.substring(startIndex, endIndex));
            
            char[] buffer = new char[contentLength];
            reader.read(buffer, 0, contentLength);
            requestBody += new String(buffer).trim();
        }

        // Extract the username from the request body
        String username = extractUsernameFromRequestBody(requestBody);

        // Construct and send the response
        outputStream.write("HTTP/1.1 200 OK\r\n");
        outputStream.write("Content-Type: text/plain\r\n");
        outputStream.write("\r\n");
        outputStream.write("Hello " + username);
        
        outputStream.flush();
    }

    private static String extractUsernameFromRequestBody(String requestBody) {
        // Simple extraction assuming a format like "username=JohnDoe"
        int startIndex = requestBody.indexOf("username=") + 9;
        if (startIndex < 9) return "";
        int endIndex = requestBody.indexOf("&", startIndex);
        if (endIndex == -1) endIndex = requestBody.length();
        return requestBody.substring(startIndex, endIndex);
    }

    public static void main(String[] args) throws IOException {
        InputStreamReader inputStream = new InputStreamReader(System.in);
        OutputStreamWriter outputStream = new OutputStreamWriter(System.out);

        http_hello_page(inputStream, outputStream);
    }
}