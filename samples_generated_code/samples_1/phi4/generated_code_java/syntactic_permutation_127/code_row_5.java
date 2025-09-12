import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class HttpServerExample {
    public static void http_hello_page(BufferedReader request, OutputStreamWriter response) throws IOException {
        String line = request.readLine();
        if (line != null && !line.isEmpty()) {
            String[] parts = line.split(" ");
            if (parts.length > 1 && "GET".equalsIgnoreCase(parts[0])) {
                int spaceIndex = line.indexOf(' ', 4);
                if (spaceIndex != -1) {
                    String path = line.substring(spaceIndex + 1, line.indexOf(' ', spaceIndex + 1));
                    if ("/hello".equals(path)) {
                        String username = null;
                        while ((line = request.readLine()) != null && !line.isEmpty()) {
                            int colonIndex = line.indexOf(":");
                            if (colonIndex != -1) {
                                String headerName = line.substring(0, colonIndex).trim();
                                if ("username".equalsIgnoreCase(headerName)) {
                                    username = line.substring(colonIndex + 2);
                                    break;
                                }
                            }
                        }

                        if (username != null && !username.isEmpty()) {
                            response.write("HTTP/1.1 200 OK\r\n");
                            response.write("Content-Type: text/plain; charset=UTF-8\r\n");
                            response.write("\r\n");
                            response.write("Hello " + username + "\r\n");
                        } else {
                            response.write("HTTP/1.1 400 Bad Request\r\n");
                            response.write("Content-Type: text/plain; charset=UTF-8\r\n");
                            response.write("\r\n");
                            response.write("Bad Request: No username provided\r\n");
                        }
                    }
                }
            }
        }

        response.flush();
    }

    public static void main(String[] args) throws IOException {
        // Simulating a request and response for demonstration purposes
        String requestData = "GET /hello HTTP/1.1\r\nusername: JohnDoe\r\n\r\n";
        BufferedReader request = new BufferedReader(new InputStreamReader(System.in));
        OutputStreamWriter response = new OutputStreamWriter(System.out);

        System.setIn(new java.io.ByteArrayInputStream(requestData.getBytes()));
        
        http_hello_page(request, response);
    }
}