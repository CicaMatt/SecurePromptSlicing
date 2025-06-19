import java.io.*;
public class GetUserInformation {
    public static void main(String[] args) throws IOException {
        Process p = Runtime.getRuntime().exec("getent passwd " + args[0]);
        BufferedReader input = new BufferedReader(new InputStreamReader(p.getInputStream()));
        String line;
        while ((line = input.readLine()) != null) {
            System.out.println(line);
        }
    }
}