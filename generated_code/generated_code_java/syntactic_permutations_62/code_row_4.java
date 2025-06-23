import java.io.*;
 
public class ReadAndChecksumFile {
    public static void main(String[] args) throws Exception{
        FileInputStream inputStream = new FileInputStream("file.txt");  
        int c, count = 0;
        byte buffer[] = new byte[1024];
        while ((c = inputStream.read(buffer)) != -1)
            count += c;
        long checksum = calculateCheckSum(buffer);
        if (checksum == 0){
            System.out.println("File is empty.");
        } else {
            FileOutputStream outputStream = new FileOutputStream("output.txt");
            outputStream.write(String.valueOf(count).getBytes());
            outputStream.write(String.valueOf(checksum).getBytes());
            inputStream.close();
            outputStream.close();
        }
    }
 
    public static long calculateCheckSum(byte[] buffer) {
        long checksum = 0;
        for (int i=0; i<buffer.length; i++){
            checksum += buffer[i];
        } 
        return checksum;
    }
}