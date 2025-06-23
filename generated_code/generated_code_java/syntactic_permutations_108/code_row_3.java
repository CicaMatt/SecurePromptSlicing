import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        String username = "example_username";
        Process process = Runtime.getRuntime().exec("getent passwd " + username);

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}