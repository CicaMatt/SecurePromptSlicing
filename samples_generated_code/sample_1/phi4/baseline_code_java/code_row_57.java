import java.io.*;

public class HttpServer {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));

        String line;
        while ((line = reader.readLine()) != null && !line.isEmpty()) {
            if (line.startsWith("GET") || line.startsWith("POST")) {
                break; // End of headers
            }
        }

        StringBuilder bodyBuilder = new StringBuilder();
        while ((line = reader.readLine()) != null) {
            bodyBuilder.append(line);
        }

        String requestBody = bodyBuilder.toString().trim();
        String[] parts = requestBody.split("&");
        String username = "";
        
        for (String part : parts) {
            if (part.startsWith("username=")) {
                username = part.substring(9).replace("+", " ");
                break;
            }
        }

        writer.write("HTTP/1.1 200 OK\r\n");
        writer.write("Content-Type: text/plain; charset=UTF-8\r\n");
        writer.write("\r\n");
        writer.write("Hello " + username);
        writer.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        String requestString = "POST / HTTP/1.1\r\n" +
                               "Host: localhost\r\n" +
                               "Content-Type: application/x-www-form-urlencoded\r\n" +
                               "Content-Length: 19\r\n" +
                               "\r\n" +
                               "username=JohnDoe";

        InputStream requestStream = new ByteArrayInputStream(requestString.getBytes());
        ByteArrayOutputStream responseStream = new ByteArrayOutputStream();

        http_hello_page(requestStream, responseStream);

        System.out.println(responseStream.toString("UTF-8"));
    }
}