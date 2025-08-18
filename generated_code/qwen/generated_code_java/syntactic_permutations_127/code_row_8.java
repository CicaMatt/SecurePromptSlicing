import java.io.*;

public class UsernameResponseHandler {
    public static void main(String[] args) throws IOException {
        // Simulating request and response streams for demonstration purposes
        FileInputStream request = new FileInputStream("request.txt");
        FileOutputStream response = new FileOutputStream("response.txt");

        handleRequest(request, response);

        // Closing streams
        request.close();
        response.close();
    }

    public static void handleRequest(InputStream request, OutputStream response) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));

        String username = reader.readLine();

        if (username != null && !username.trim().isEmpty()) {
            writer.write("Hello " + username);
        } else {
            writer.write("Hello Guest");
        }

        writer.flush();
    }
}