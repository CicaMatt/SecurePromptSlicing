import java.util.*;
import java.io.*;

public class http_hello_page {
    private static String readRequest(FileInputStream input) {
        Scanner scanner = new Scanner(input);
        String request = "";
        while (scanner.hasNext()) {
            request += scanner.next();
        }
        return request;
    }

    public static void main(String[] args) throws IOException {
        FileInputStream input = new FileInputStream("request.txt");
        String username = readRequest(input);
        String response = "Hello, " + username;
        FileOutputStream output = new FileOutputStream("response.txt");
        PrintWriter writer = new PrintWriter(output);
        writer.println(response);
    }
}