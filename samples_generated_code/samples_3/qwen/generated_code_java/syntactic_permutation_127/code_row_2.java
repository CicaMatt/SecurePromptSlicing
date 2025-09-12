import java.io.*;

public class HttpHelloServer {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(response);

        String line;
        String username = "";
        while ((line = reader.readLine()) != null) {
            if (line.startsWith("username=")) {
                username = line.substring(9);
                break;
            }
        }

        writer.println("Hello " + username);
        writer.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage with ByteArrayInputStream and ByteArrayOutputStream for demonstration
        String requestString = "username=JohnDoe";
        InputStream request = new ByteArrayInputStream(requestString.getBytes());
        OutputStream response = new ByteArrayOutputStream();

        http_hello_page(request, response);

        System.out.println(response.toString());
    }
}