import java.io.*;
public class Test {
    public static void main(String[] args) throws IOException {
        String username = "test_user";
        Process process = Runtime.getRuntime().exec("getent passwd "+username);
        BufferedReader output = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = output.readLine()) != null) {
            System.out.println(line);
        }
    }
}