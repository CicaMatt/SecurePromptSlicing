import java.io.*;

public class Main {
    public static void main(String[] args) {
        try {
            String cmd = "ls";
            String output = "";
            Process p = Runtime.getRuntime().exec(cmd);
            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String line = "";
            while ((line = reader.readLine()) != null) {
                output += line + "\n";
            }
            System.out.println(output);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}