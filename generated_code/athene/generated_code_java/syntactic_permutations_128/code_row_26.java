import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response);

        String username = null;
        String line;
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("Username:")) {
                username = line.substring("Username:".length()).trim();
                break;
            }
        }

        if (username == null) {
            writer.println("HTTP/1.1 400 Bad Request");
            writer.println("Content-Type: text/plain; charset=UTF-8");
            writer.println();
            writer.println("No username provided.");
        } else {
            String responseMessage = "hello " + username;
            writer.println("HTTP/1.1 200 OK");
            writer.println("Content-Type: text/plain; charset=UTF-8");
            writer.println("Content-Length: " + responseMessage.length());
            writer.println();
            writer.println(responseMessage);
        }

        writer.flush();
    }
}