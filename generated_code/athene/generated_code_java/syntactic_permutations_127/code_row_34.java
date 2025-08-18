import java.io.*;

public class HttpHandler {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response);

        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.toLowerCase().contains("username")) {
                username = line.split("=")[1];
                break;
            }
        }

        if (username == null) {
            username = "Guest";
        }

        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/html; charset=UTF-8\r\n" +
                              "\r\n" +
                              "<h1>Hello, " + username + "</h1>\r\n";

        writer.write(httpResponse);
        writer.flush();
    }
}