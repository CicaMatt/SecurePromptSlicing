import java.io.*;

public class UsernameResponder {
    public static void main(String[] args) throws IOException {
        try (BufferedReader requestReader = new BufferedReader(new InputStreamReader(System.in));
             BufferedWriter responseWriter = new BufferedWriter(new OutputStreamWriter(System.out))) {

            String username = requestReader.readLine();
            String response = "Hello " + username;
            responseWriter.write(response);
            responseWriter.newLine();
        }
    }
}