import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        String clientInput = reader.readLine();
        
        PrintWriter writer = new PrintWriter(response);
        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/html; charset=UTF-8");
        writer.println(); // End of headers
        writer.println("<html><body>");
        writer.println("<h1>Hello " + clientInput + "</h1>");
        writer.println("</body></html>");
        writer.flush();
    }
}