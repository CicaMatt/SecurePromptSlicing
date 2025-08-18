import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = null;
        while (reader.ready()) {
            String line = reader.readLine();
            if (line.startsWith("username=")) {
                username = line.substring(9);
                break;
            }
        }

        if (username != null) {
            writer.println("HTTP/1.1 200 OK");
            writer.println("Content-Type: text/plain; charset=UTF-8");
            writer.println();
            writer.println("hello " + username);
        } else {
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println("Content-Type: text/plain; charset=UTF-8");
            writer.println();
            writer.println("Username not provided.");
        }

        writer.flush();
    }
}