import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException, InterruptedException {
        String username = "user";
        Process process = Runtime.getRuntime().exec("getent passwd " + username);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        File file = new File("/tmp/output");
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        String line;
        while ((line = reader.readLine()) != null) {
            writer.write(line);
            writer.newLine();
        }
        writer.close();
    }
}