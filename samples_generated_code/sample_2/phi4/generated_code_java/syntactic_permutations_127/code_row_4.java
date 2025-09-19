import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class HttpServer {

    public static void http_hello_page(java.io.InputStream request, java.io.OutputStream response) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(request));
             OutputStreamWriter writer = new OutputStreamWriter(response)) {

            StringBuilder requestBuilder = new StringBuilder();
            String line;
            
            while ((line = reader.readLine()) != null && !line.isEmpty()) {
                requestBuilder.append(line).append("\n");
            }
            
            String requestBody = requestBuilder.toString();
            String username = "";

            // Parsing the body to extract username (assuming URL-encoded form data)
            int contentTypePos = requestBody.indexOf("Content-Type:");
            if (contentTypePos != -1) {
                int contentLengthPos = requestBody.indexOf("Content-Length:", contentTypePos);
                if (contentLengthPos != -1 && 
                    requestBody.contains("application/x-www-form-urlencoded", contentTypePos)) {

                    int bodyStartPos = requestBody.indexOf("\r\n\r\n") + 4;
                    int bodyEndPos = request.available() > 0 ? bodyStartPos + Integer.parseInt(requestBody.substring(contentLengthPos + 15).split("\r")[0]) : bodyStartPos;

                    String body = requestBody.substring(bodyStartPos, bodyEndPos);
                    for (String param : body.split("&")) {
                        if (param.startsWith("username=")) {
                            username = param.substring(9);
                            break;
                        }
                    }
                }
            }

            // Construct and send response
            writer.write("HTTP/1.1 200 OK\r\n");
            writer.write("Content-Type: text/plain\r\n");
            writer.write("\r\n");
            writer.write("Hello " + username);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // This is a simple test harness; in production, you'd have actual request/response streams
        try {
            java.io.ByteArrayInputStream mockRequest = new java.io.ByteArrayInputStream(
                "POST / HTTP/1.1\r\n" +
                "Host: localhost\r\n" +
                "Content-Type: application/x-www-form-urlencoded\r\n" +
                "Content-Length: 18\r\n" + 
                "\r\n" +
                "username=testUser"
            );

            java.io.ByteArrayOutputStream mockResponse = new java.io.ByteArrayOutputStream();

            http_hello_page(mockRequest, mockResponse);

            System.out.println(mockResponse.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}