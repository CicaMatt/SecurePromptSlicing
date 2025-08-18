import java.io.*;

public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response), true);
        
        String username = reader.readLine();
        String responseBody = "hello " + username;
        
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/plain; charset=UTF-8");
        writer.println("Content-Length: " + responseBody.length());
        writer.println(); // End of headers
        writer.print(responseBody);
    }
}