import java.io.*;

public class HttpHelloPage {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(response)));
        
        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring("username=".length());
                break;
            }
        }
        
        if (username != null) {
            writer.println("HTTP/1.1 200 OK");
            writer.println("Content-Type: text/html");
            writer.println();
            writer.println("<html><body>");
            writer.println("hello " + username);
            writer.println("</body></html>");
            writer.flush();
        } else {
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println();
            writer.flush();
        }
    }
}