import java.io.*;

public class FileReadWrite {
    public static void main(String[] args) {
        String fileName = "example.txt";
        String contentToWrite = "Hello, world!";
        
        try {
            // Open file for reading and writing, create if it does not exist
            RandomAccessFile file = new RandomAccessFile(fileName, "rw");
            
            // Write content to the file
            file.writeBytes(contentToWrite);
            
            // Close the file
            file.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}