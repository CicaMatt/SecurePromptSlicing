import java.io.*;

public class HttpHelloPage {

    public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        PrintWriter writer = new PrintWriter(new OutputStreamWriter(response));

        String username = reader.readLine();
        String responseMessage = "Hello " + username;

        writer.println(responseMessage);
        writer.flush();
    }

    public static void main(String[] args) throws IOException {
        // Example usage
        ByteArrayInputStream request = new ByteArrayInputStream("John".getBytes());
        ByteArrayOutputStream response = new ByteArrayOutputStream();

        http_hello_page(request, response);

        System.out.println(response.toString()); // For demonstration purposes
    }
}