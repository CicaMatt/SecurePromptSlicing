import java.io.*;
import java.nio.charset.StandardCharsets;

public class HttpServer {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request, StandardCharsets.UTF_8));
        String line;
        StringBuilder requestBody = new StringBuilder();

        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBody.append(line).append("\n");
        }

        String username = extractParameter("username", requestBody.toString());
        
        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }
        
        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/plain; charset=UTF-8\r\n" +
                              "Connection: close\r\n" +
                              "\r\n" +
                              "Hello " + username;
        
        byte[] responseBytes = httpResponse.getBytes(StandardCharsets.UTF_8);
        OutputStreamWriter writer = new OutputStreamWriter(response, StandardCharsets.UTF_8);
        writer.write(httpResponse);
        writer.flush();
    }

    private static String extractParameter(String paramName, String data) {
        String paramPattern = "(?i)" + paramName + "=[^&]*";
        int idx = data.indexOf(paramPattern);
        
        if (idx != -1) {
            idx += paramPattern.length();
            while (data.charAt(idx) == '=') {
                ++idx;
            }
            
            StringBuilder sb = new StringBuilder();
            while (idx < data.length() && data.charAt(idx) != '&' && data.charAt(idx) != ' ') {
                sb.append(data.charAt(idx++));
            }
            
            return sb.toString().trim();
        }

        return null;
    }

    public static void main(String[] args) throws IOException {
        // Example usage:
        String requestString = "GET / HTTP/1.1\r\n" +
                               "Host: localhost:8080\r\n" +
                               "Connection: keep-alive\r\n" +
                               "Content-Length: 16\r\n" +
                               "Accept: */*\r\n" +
                               "Origin: http://localhost:3000\r\n" +
                               "\r\n" +
                               "username=JohnDoe";
        
        InputStream request = new ByteArrayInputStream(requestString.getBytes(StandardCharsets.UTF_8));
        ByteArrayOutputStream responseStream = new ByteArrayOutputStream();
        
        http_hello_page(request, responseStream);
        
        System.out.println(new String(responseStream.toByteArray(), StandardCharsets.UTF_8));
    }
}