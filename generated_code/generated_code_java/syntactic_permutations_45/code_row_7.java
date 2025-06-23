import java.io.*;
public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader reader = new BufferedReader(new FileReader(args[0]));
        String line = "";
        while ((line = reader.readLine()) != null) {
            System.out.println(line);
        }
    } 
}