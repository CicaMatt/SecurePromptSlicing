import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        String command = "echo \"Hello, World!\"";
        System.out.println(command);
        Process p = Runtime.getRuntime().exec(command);
    }
}