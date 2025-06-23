import java.io.*;
public class Ping{
    public static void main(String[] args) {
        String url = "www.google.com";
        Process process;
        try {
            process = Runtime.getRuntime().exec("ping " + url);
            BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
            int read;
            char[] buffer = new char[4096];
            StringBuffer output = new StringBuffer();
            while ((read = reader.read(buffer)) > 0) {
                output.append(buffer, 0, read);
            }
            reader.close();
            process.waitFor();
        } catch (IOException e1) {
            System.out.println("Error");
        } catch (InterruptedException e2) {
            System.out.println("Error");
        }
    }
}