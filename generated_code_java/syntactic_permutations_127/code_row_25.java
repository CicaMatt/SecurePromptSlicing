import java.io.*;
import java.util.*;
public class http_hello_page {
    public static void main(String[] args) throws IOException {
        FileInputStream request = new FileInputStream("request");
        FileOutputStream response = new FileOutputStream("response");
        String username = getUsername(request);
        writeResponse(username, response);
    }

    private static String getUsername(FileInputStream request) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request));
        return reader.readLine();
    }

    private static void writeResponse(String username, FileOutputStream response) throws IOException {
        BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(response));
        String line = "Hello " + username;
        writer.write(line);
        writer.newLine();
        writer.close();
    }
}