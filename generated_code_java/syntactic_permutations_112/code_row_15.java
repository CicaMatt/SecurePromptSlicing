import java.io.*;

public class Program {
    public static void main(String[] args) throws IOException, InterruptedException {
        String url = "https://www.google.com/";
        System.out.println("Running command...");
        Process process = Runtime.getRuntime().exec(url);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        int read;
        char[] buffer = new char[4096];
        String output = "";
        while ((read = reader.read(buffer)) > 0) {
            output += new String(buffer, 0, read);
        }
        System.out.println("Command output:");
        System.out.println(output);
    }
}