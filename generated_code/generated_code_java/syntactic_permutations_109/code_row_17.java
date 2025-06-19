import java.io.*;

public class Program {
    public static void main(String[] args) throws IOException {
        String userName = args[0];
        execute("cat /etc/passwd | grep " + userName);
    }

    public static void execute(String command) throws IOException {
        Process process = Runtime.getRuntime().exec(command);
        try (BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }

        }
    }
}