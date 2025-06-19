import java.io.*;
public class Ping {
    public static void main(String[] args) {
        String url = "www.google.com";
        try {
            Process process = Runtime.getRuntime().exec("ping -c 3 www.google.com");
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            int read;
            char[] buffer = new char[4096];
            StringBuffer output = new StringBuffer();
            while ((read = reader.read(buffer)) > 0) {
                output.append(buffer, 0, read);
            }
            reader.close();
            process.waitFor();
        } catch (Exception e) {
            System.out.println("Failed to run the command " + e);
        }
    }
}