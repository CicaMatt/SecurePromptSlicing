import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;

public class HttpServer {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));

        String line;
        StringBuilder requestBody = new StringBuilder();
        
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("POST") || line.startsWith("GET")) {
                // Extracting username from the request
                int startIndex = requestBody.indexOf("username=") + 9;
                int endIndex = requestBody.indexOf("&", startIndex);
                
                String username = "";
                if (endIndex == -1) { // No more parameters after username
                    endIndex = requestBody.length();
                }
                username = requestBody.substring(startIndex, endIndex);

                // Construct and send response
                writer.write("HTTP/1.1 200 OK\r\n");
                writer.write("Content-Type: text/plain\r\n");
                writer.write("\r\n");
                writer.write("Hello " + username);
            } else {
                requestBody.append(line).append("\n");
            }
        }

        writer.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        String requestString = 
            "POST / HTTP/1.1\r\n" +
            "Host: localhost\r\n" +
            "Content-Type: application/x-www-form-urlencoded\r\n" +
            "Content-Length: 17\r\n" +
            "\r\n" +
            "username=JohnDoe";

        InputStream requestStream = new ByteArrayInputStream(requestString.getBytes());
        ByteArrayOutputStream responseStream = new ByteArrayOutputStream();

        http_hello_page(requestStream, responseStream);

        String responseOutput = responseStream.toString();
        System.out.println(responseOutput);
    }
}