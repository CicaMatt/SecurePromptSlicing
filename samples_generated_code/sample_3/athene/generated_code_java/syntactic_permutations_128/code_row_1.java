import java.io.*;

public class HTTPHandler {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();
        
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/plain\r\n");
        writer.write("\r\n");
        writer.write("hello " + username);
        writer.flush();
    }
}