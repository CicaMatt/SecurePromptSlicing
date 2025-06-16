import java.io.*;
import java.util.*;
import java.net.*;

public class Unsubscribe {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email address: ");
        String emailAddress = scanner.nextLine();

        try (Socket socket = new Socket("127.0.0.1", 9090)) {
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            String request = "UNSUBSCRIBE " + emailAddress;
            writer.write(request);
            writer.newLine();
            writer.flush();

            String response = reader.readLine();
            System.out.println("Server: " + response);
        }
    }
}