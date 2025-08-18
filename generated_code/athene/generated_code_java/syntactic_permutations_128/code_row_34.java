import java.io.*;

public class HttpHelloPage {

    public void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response);

        String line;
        StringBuilder headers = new StringBuilder();
        while (!(line = reader.readLine()).isEmpty()) {
            headers.append(line).append("\n");
        }

        String username = extractUsername(headers.toString());
        String responseContent = "HTTP/1.1 200 OK\r\n" +
                                 "Content-Type: text/html\r\n" +
                                 "Content-Length: " + ("hello " + username).length() + "\r\n" +
                                 "\r\n" +
                                 "hello " + username;

        writer.write(responseContent);
        writer.flush();
    }

    private String extractUsername(String headers) {
        String[] lines = headers.split("\n");
        for (String line : lines) {
            if (line.startsWith("username:")) {
                return line.substring(line.indexOf(":") + 1).trim();
            }
        }
        return "Anonymous";
    }
}