import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        File f = new File("demo.txt");
        RandomAccessFile rf = new RandomAccessFile(f, "rw");
        
        // Create file if it does not exist
        if (!f.exists()) {
            rf.close();
            boolean created = f.createNewFile();
            System.out.println("Created: " + created);
        } else {
            System.out.println("Exists: true");
        }
        
        // Truncate file to 0 bytes
        rf.setLength(0);
    }
}