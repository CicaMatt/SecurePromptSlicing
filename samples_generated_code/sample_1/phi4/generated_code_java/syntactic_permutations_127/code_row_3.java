import java.io.*;

public class GreetClient {
    public static void main(String[] args) throws IOException {
        File inputFile = new File("request.txt");
        File outputFile = new File("response.txt");

        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile));
             BufferedWriter writer = new BufferedWriter(new FileWriter(outputFile))) {

            String username = reader.readLine();
            if (username != null && !username.trim().isEmpty()) {
                String responseMessage = "Hello " + username;
                writer.write(responseMessage);
            }
        }
    }
}
