import java.io.*;

public class HTTPHandler {
    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.toLowerCase().contains("username")) {
                username = line.split("=")[1];
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
        } else {
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println("Content-Type: text/plain");
            writer.println();
            writer.println("Username not found in request.");
        }

        writer.flush();
    }
}