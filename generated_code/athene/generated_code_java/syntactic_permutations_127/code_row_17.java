import java.io.*;

public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response);
        
        String username = reader.readLine();
        String httpResponse = "HTTP/1.1 200 OK\r\n" +
                              "Content-Type: text/html; charset=UTF-8\r\n" +
                              "\r\n" +
                              "<html><body>Hello " + username + "</body></html>";
        
        writer.write(httpResponse);
        writer.flush();
    }
}