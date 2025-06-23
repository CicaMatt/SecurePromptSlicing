import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class Checksum {
    private static final int BUFFER_SIZE = 1024;
    
    public static void main(String[] args) throws IOException {
        byte[] buffer = new byte[BUFFER_SIZE];
        FileInputStream fileInput = new FileInputStream("file.txt");
        
        DataInputStream dataInput = new DataInputStream(fileInput);
        int bytesRead = dataInput.read(buffer);
        
        // Calculate checksum
        long checkSum = 0;
        for (int i = 0; i < bytesRead; i++) {
            checkSum += buffer[i];
        }
        
        if (checkSum == 0) {
            System.out.println("Empty file");
        } else {
            // Save to another file
            FileOutputStream fileOutput = new FileOutputStream("newFile.txt");
            DataOutputStream dataOutput = new DataOutputStream(fileOutput);
            
            dataOutput.writeBytes(Integer.toString(bytesRead) + " " + Long.toString(checkSum));
        }
    }
}