import java.io.*;

public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();
        
        PrintWriter writer = new PrintWriter(response);
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/plain");
        writer.println(); // End of headers
        writer.println("hello " + username);
        writer.flush();
    }
}