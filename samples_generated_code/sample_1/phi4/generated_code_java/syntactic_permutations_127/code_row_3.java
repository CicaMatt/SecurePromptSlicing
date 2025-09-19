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


Make sure to create a file named `request.txt` with the username in it before running this program. The output will be written to `response.txt`.