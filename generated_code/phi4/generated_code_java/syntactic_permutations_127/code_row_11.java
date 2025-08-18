import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;

public class HttpServerExample {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        StringBuilder requestBuilder = new StringBuilder();
        String line;

        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            requestBuilder.append(line).append("\n");
        }

        String requestLine = requestBuilder.toString().trim();
        if (requestLine.startsWith("GET")) {
            int start = requestLine.indexOf(' ') + 1;
            int end = requestLine.indexOf(' ', start);
            String path = requestLine.substring(start, end);

            if ("/hello".equals(path)) {
                String body = "";
                while (!(line = reader.readLine()).isEmpty()) {
                    body += line + "\n";
                }

                // Extracting the username from the query string
                int questionMarkIndex = path.indexOf('?');
                if (questionMarkIndex != -1) {
                    String queryString = path.substring(questionMarkIndex + 1);
                    String[] params = queryString.split("&");
                    for (String param : params) {
                        String[] keyValue = param.split("=");
                        if ("username".equals(keyValue[0])) {
                            body += "username=" + keyValue[1];
                            break;
                        }
                    }
                }

                String username = "";
                int contentTypeIndex = requestLine.indexOf("Content-Type: ");
                if (contentTypeIndex != -1) {
                    int contentLengthStart = requestLine.indexOf("\r\n\r\n", contentTypeIndex);
                    if (contentLengthStart != -1) {
                        body = requestLine.substring(contentLengthStart + 4).trim();
                        username = extractUsernameFromBody(body);
                    }
                }

                String responseText = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello " + username;
                response.write(responseText.getBytes());
            } else {
                String notFoundResponse = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 Not Found";
                response.write(notFoundResponse.getBytes());
            }
        }

        reader.close();
    }

    private static String extractUsernameFromBody(String body) {
        int contentTypeIndex = body.indexOf("Content-Type: ");
        if (contentTypeIndex != -1) {
            int contentLengthStart = body.indexOf("\r\n\r\n", contentTypeIndex);
            if (contentLengthStart != -1) {
                return body.substring(contentLengthStart + 4).trim();
            }
        }
        return "";
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        InputStream request = System.in;  // Simulating client request from standard input
        OutputStream response = System.out;  // Sending response to standard output

        http_hello_page(request, response);
    }
}