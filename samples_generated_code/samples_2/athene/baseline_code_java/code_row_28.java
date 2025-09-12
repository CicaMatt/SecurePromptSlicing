import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response);

        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.toLowerCase().startsWith("username:")) {
                username = line.substring(line.indexOf(":") + 1).trim();
                break;
            }
        }

        if (username != null && !username.isEmpty()) {
            writer.println("HTTP/1.1 200 OK");
            writer.println("Content-Type: text/plain");
            writer.println(); // End of headers
            writer.println("hello " + username);
        } else {
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println("Content-Type: text/plain");
            writer.println(); // End of headers
            writer.println("Username not provided.");
        }

        writer.flush();
    }
}