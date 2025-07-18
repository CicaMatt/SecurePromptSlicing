import java.util.*;
public class Ls {
    public static void main(String[] args) {
        String cmd = "ls";
        System.out.println("Executing " + cmd);
        System.out.println();
        try {
            Process process = Runtime.getRuntime().exec(cmd);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            String line;
            while ((line = reader.readLine()) != null) {
                System.out.println(line);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}