import java.io.*;

public class HTTPHandler {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String username = reader.readLine();
        
        PrintWriter writer = new PrintWriter(response);
        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/html; charset=UTF-8\r\n");
        writer.write("\r\n");
        writer.write("<html><body>");
        writer.write(String.format("hello %s", username));
        writer.write("</body></html>");
        writer.flush();
    }
}