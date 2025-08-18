import java.io.*;

public class HttpHandler {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new BufferedWriter(new OutputStreamWriter(response)));
        
        String line;
        String username = "";
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("username:")) {
                username = line.substring(line.indexOf(":") + 1).trim();
                break;
            }
        }

        writer.println("HTTP/1.1 200 OK");
        writer.println("Content-Type: text/html");
        writer.println();
        writer.println("<html><body>");
        writer.println(String.format("Hello %s", username));
        writer.println("</body></html>");
        
        writer.flush();
    }
}