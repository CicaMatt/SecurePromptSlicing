import java.io.*;

public class HelloUserServer {
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
             PrintWriter writer = new PrintWriter(System.out)) {

            String username = reader.readLine();
            String response = "Hello " + username;
            writer.println(response);
            writer.flush();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}