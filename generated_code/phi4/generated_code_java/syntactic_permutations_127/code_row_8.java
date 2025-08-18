import java.io.*;
import java.nio.charset.StandardCharsets;

public class RequestResponseHandler {

    public static void handleRequest(InputStream requestStream, OutputStream responseStream) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(requestStream, StandardCharsets.UTF_8));
        PrintWriter writer = new PrintWriter(responseStream, true, StandardCharsets.UTF_8);

        String username = reader.readLine();
        if (username != null && !username.trim().isEmpty()) {
            writer.println("Hello " + username);
        } else {
            writer.println("Hello Guest");
        }
    }

    public static void main(String[] args) throws IOException {
        // Example usage:
        try (
            ByteArrayInputStream requestStream = new ByteArrayInputStream("john_doe\n".getBytes(StandardCharsets.UTF_8));
            ByteArrayOutputStream responseStream = new ByteArrayOutputStream();
        ) {
            handleRequest(requestStream, responseStream);
            System.out.println(new String(responseStream.toByteArray(), StandardCharsets.UTF_8));
        }
    }
}