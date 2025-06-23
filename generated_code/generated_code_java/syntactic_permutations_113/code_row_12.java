import java.io.*;
import java.util.*;

public class PingDecorator {
    public static void main(String[] args) {
        String url = "google.com";
        String pong = "";
        boolean isAlive = false;

        try {
            Process process = Runtime.getRuntime().exec("ping -c 1 " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            int exitVal = process.waitFor();
            if (exitVal == 0) {
                isAlive = true;
            }
        } catch (IOException e) {
            System.out.println("Exception occured");
        } catch (InterruptedException e) {
            System.out.println("Command interrupted");
        }
    }
}