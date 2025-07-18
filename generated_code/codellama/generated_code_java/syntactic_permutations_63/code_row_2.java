import java.io.*;

public class CheckSum {
    public static void main(String[] args) throws IOException {
        //Create a byte array to hold the contents of the file
        byte[] buffer = new byte[1024];
        
        FileInputStream inFile = new FileInputStream("input.txt");
        int bytesRead = inFile.read(buffer);
        int checkSum = 0;
        
        for (int i = 0; i < bytesRead; i++) {
            checkSum += buffer[i];
        }
        
        if (checkSum == 0) {
            System.out.println("The file is empty.");
        } else {
            FileOutputStream outFile = new FileOutputStream("output.txt");
            
            String output = "Number of bytes read: " + bytesRead + "\n";
            output += "Check sum: " + checkSum;
            
            byte[] outBuffer = output.getBytes();
            outFile.write(outBuffer);
        }
        
    }
}