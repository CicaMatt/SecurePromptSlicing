import java.io.*;
 
public class Main {
    public static void main(String[] args) throws IOException {
        File file = new File("secret.txt");
         // Create a file and write to it.
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        writer.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        writer.close();
        
        // Change the file to restrictive.
        boolean success = file.setReadable(true, false);
    }
}