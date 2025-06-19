import java.io.*;

public class App {
    public static void main(String[] args) throws Exception {
        // Generate file with secret code inside
        FileWriter myWriter = new FileWriter("secret.txt");
        myWriter.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        myWriter.close();
        
        // Change permissions of file to restrictive
        ProcessBuilder pb = new ProcessBuilder("chmod", "000","secret.txt");
        Process process = pb.start();
    }
}