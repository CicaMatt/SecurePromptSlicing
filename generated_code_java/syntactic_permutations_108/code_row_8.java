import java.io.*;

public class Getent {
    public static void main(String[] args) throws IOException, InterruptedException {
        String username = "username";
        Process process = Runtime.getRuntime().exec("getent passwd "+username);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}