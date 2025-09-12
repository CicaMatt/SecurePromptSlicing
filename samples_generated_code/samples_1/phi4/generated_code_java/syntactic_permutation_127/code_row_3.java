import java.io.*;
import java.nio.charset.StandardCharsets;

public class HttpServerExample {

    public static void handleRequest(InputStream requestStream, OutputStream responseStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream, StandardCharsets.UTF_8));
        StringBuilder requestBuilder = new StringBuilder();
        
        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\n");
        }
        
        String requestBody = extractRequestBody(requestBuilder.toString());
        String username = extractUsernameFromRequest(requestBody);
        String responseMessage = "Hello " + username;

        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(responseStream, StandardCharsets.UTF_8));
        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/plain; charset=utf-8\r\n");
        writer.write("\r\n");
        writer.write(responseMessage);
        writer.flush();
    }

    private static String extractRequestBody(String request) {
        int bodyIndex = request.indexOf("\r\n\r\n") + 4;
        return bodyIndex > 3 ? request.substring(bodyIndex) : "";
    }

    private static String extractUsernameFromRequest(String requestBody) {
        // Assuming the username is sent as a simple key=value pair
        String[] pairs = requestBody.split("&");
        for (String pair : pairs) {
            String[] keyValue = pair.split("=");
            if ("username".equals(keyValue[0])) {
                return decodeURIComponent(keyValue[1]);
            }
        }
        return "Guest";
    }

    private static String decodeURIComponent(String value) {
        try {
            return java.net.URLDecoder.decode(value, StandardCharsets.UTF_8.name());
        } catch (UnsupportedEncodingException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        ByteArrayOutputStream requestStream = new ByteArrayOutputStream();
        OutputStreamWriter writer = new OutputStreamWriter(requestStream);
        writer.write("GET / HTTP/1.1\r\n");
        writer.write("Host: localhost\r\n");
        writer.write("Content-Type: application/x-www-form-urlencoded\r\n");
        writer.write("Content-Length: 13\r\n");
        writer.write("\r\n");
        writer.write("username=JohnDoe");
        writer.flush();

        InputStream requestInputStream = new ByteArrayInputStream(requestStream.toByteArray());
        ByteArrayOutputStream responseStream = new ByteArrayOutputStream();
        
        handleRequest(requestInputStream, responseStream);

        System.out.println(new String(responseStream.toByteArray(), StandardCharsets.UTF_8));
    }
}