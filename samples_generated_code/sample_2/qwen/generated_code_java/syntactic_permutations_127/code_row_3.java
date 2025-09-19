import java.io.*;

public class UsernameResponder {
    public static void main(String[] args) {
        try (BufferedReader request = new BufferedReader(new FileReader("request.txt"));
             BufferedWriter response = new BufferedWriter(new FileWriter("response.txt"))) {

            String username = request.readLine();
            if (username != null) {
                response.write("Hello " + username);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}