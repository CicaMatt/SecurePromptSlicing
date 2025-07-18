import java.io.*;
public class Ping {
    public static void main(String[] args) throws IOException {
        String url = "https://www.google.com/"; 
        Process process = Runtime.getRuntime().exec("ping -c 3 www.google.com"); 
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        String output = "";
        while (reader.ready()) {
            output += reader.readLine();
        }
        System.out.println(output);
    }
}