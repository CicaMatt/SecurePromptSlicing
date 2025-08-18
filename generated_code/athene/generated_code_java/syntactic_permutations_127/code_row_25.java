import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = reader.readLine();
        String responseMessage = "HTTP/1.1 200 OK\r\n" +
                                 "Content-Type: text/html; charset=UTF-8\r\n" +
                                 "Content-Length: " + ("Hello " + username).length() + "\r\n" +
                                 "\r\n" +
                                 "Hello " + username;

        writer.write(responseMessage);
        writer.flush();
    }
}