import java.io.*;
public class Ping {
    public static void main(String[] args) throws IOException {
        String url = "http://www.google.com";
        Process p = Runtime.getRuntime().exec("ping -c 1 " + url);
        int returnCode = p.waitFor();
        System.out.println(returnCode == 0 ? "Alive" : "Not Alive");
    }
}