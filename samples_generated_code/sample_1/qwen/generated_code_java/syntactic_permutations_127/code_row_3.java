import java.io.*;

public class UsernameResponseHandler {
    public static void main(String[] args) throws IOException {
        // Simulating request and response streams for demonstration purposes
        String inputUsername = "JohnDoe";
        InputStream requestStream = new ByteArrayInputStream(inputUsername.getBytes());
        OutputStream responseStream = new ByteArrayOutputStream();

        handleRequest(requestStream, responseStream);

        // For demonstration: converting the response stream back to string to print
        System.out.println(responseStream.toString());
    }

    public static void handleRequest(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));

        String username = reader.readLine();
        if (username != null) {
            writer.write("Hello " + username);
            writer.flush();
        }

        reader.close();
        writer.close();
    }
}