import java.io.*;
import java.util.Scanner;

public class HttpServer {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        Scanner scanner = new Scanner(request).useDelimiter("\\A");
        String requestData = scanner.hasNext() ? scanner.next() : "";
        
        int usernameStart = requestData.indexOf("username=") + "username=".length();
        int usernameEnd = requestData.indexOf('&', usernameStart);
        if (usernameEnd == -1) {
            usernameEnd = requestData.length();
        }
        String username = requestData.substring(usernameStart, usernameEnd);

        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                             "Content-Type: text/plain\r\n" +
                             "\r\n" +
                             "Hello " + username;

        response.write(httpResponse.getBytes());
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        String mockRequest = "GET /?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n";
        InputStream requestStream = new ByteArrayInputStream(mockRequest.getBytes());
        ByteArrayOutputStream responseStream = new ByteArrayOutputStream();

        http_hello_page(requestStream, responseStream);

        System.out.println(responseStream.toString());
    }
}