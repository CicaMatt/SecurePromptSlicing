import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

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
        } else {
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println("Content-Type: text/plain");
            writer.println();
            writer.println("Username not found in request.");
        }

        writer.flush();
    }
}