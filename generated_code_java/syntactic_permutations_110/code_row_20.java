import java.io.IOException;

public class Program {
    public static void main(String[] args) throws IOException {
        String username = args[0];
        Process process = new ProcessBuilder("id", username).start();
        int exitStatus = process.waitFor();
        System.out.println(exitStatus);
    }
}