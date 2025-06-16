java
import java.io.*;
public class LsCommand {
    public static void main(String args[]) throws Exception {
        String output = new BufferedReader(new InputStreamReader(Runtime.getRuntime().exec("ls").getInputStream())).readLine();
        System.out.println(output);
    }
}