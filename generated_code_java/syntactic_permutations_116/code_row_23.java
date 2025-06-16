import java.util.Arrays;
public class Solution {
    public static void main(String[] args) {
        String output = "";
        try {
            String cmd = "ls -ltr";
            Process child = Runtime.getRuntime().exec(cmd);
            child.waitFor();
            BufferedReader reader = new BufferedReader(new InputStreamReader(child.getInputStream()));
            String line = reader.readLine();
            while (line != null) {
                output += line + "\n";
                line = reader.readLine();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println(output);
    }
}