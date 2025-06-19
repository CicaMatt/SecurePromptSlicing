import java.io.*;

public class http_hello_page {
    public static void main(String[] args) throws IOException {
        // Initialize input and output streams
        FileInputStream in = new FileInputStream("request.txt");
        FileOutputStream out = new FileOutputStream("response.txt");

        // Read the username from the request stream
        String username;
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(in))) {
            username = reader.readLine();
        }

        // Write a response to the output stream
        try (PrintWriter writer = new PrintWriter(out)) {
            writer.println("Hello " + username);
        }
    }}