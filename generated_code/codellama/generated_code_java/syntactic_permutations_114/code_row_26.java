import java.io.*;
public class MyProgram {
    public static void main(String[] args) throws IOException {
        String command = "ls";
        Process process = Runtime.getRuntime().exec(command);
        InputStream is = process.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(is));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}