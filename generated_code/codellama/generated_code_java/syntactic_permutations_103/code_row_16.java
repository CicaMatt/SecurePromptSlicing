import java.io.*;
import java.lang.*;
public class File { 
    public static void main(String[] args) throws IOException {
        File file = new File("test.txt");
        try {
            boolean success = file.createNewFile();
            if (success) {
                System.out.println("File created successfully.");
            } else {
                System.out.println("Could not create file.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred while creating the file.");
        }
    } 
}