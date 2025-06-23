import java.io.IOException;
public class Main {
    public static void main(String[] args) throws IOException {
        String output = System.getProperty("user.dir") + "\\src";
        Process process = Runtime.getRuntime().exec("ls -al " + output);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String line;
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    }
}