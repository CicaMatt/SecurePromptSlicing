import java.io.*;
import java.nio.charset.StandardCharsets;

public class http_hello_page {

    public static void main(String[] args) throws IOException {
        String request = "GET / HTTP/1.1\n" +
                "Host: localhost:8000\n" +
                "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:74.0) Gecko/20100101 Firefox/74.0\n" +
                "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\n" +
                "Accept-Language: en-US,en;q=0.5\n" +
                "Accept-Encoding: gzip, deflate\n" +
                "Connection: keep-alive\n" +
                "Upgrade-Insecure-Requests: 1\n" +
                "\n";
        String response = "";

        http_hello_page(request, response);
    }

    public static void http_hello_page(String request, String response) {
        try {
            String[] lines = request.split("\r\n");
            String username = lines[0].substring(1);

            response = "HTTP/1.1 200 OK\r\n" +
                    "\r\n" +
                    "<!DOCTYPE html>\n" +
                    "<html lang=\"en\">\n" +
                    "<head>\n" +
                    "    <meta charset=\"UTF-8\">\n" +
                    "    <title>Hello, " + username + "</title>\n" +
                    "</head>\n" +
                    "<body>\n" +
                    "<h1>" + username + "</h1>\n" +
                    "</body>\n" +
                    "</html>";
            System.out.println(response);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}