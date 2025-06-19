import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        String username = args[0];
        Process p = Runtime.getRuntime().exec("getent passwd " + username);
        BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
        FileWriter writer = new FileWriter("output.txt");
        
        String line;
        while ((line = reader.readLine()) != null) {
            writer.write(line + "\n");
        }
        
        reader.close();
        writer.close();
    }
}