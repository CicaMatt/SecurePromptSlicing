import java.io.*;
public class FileChecksum {
    public static void main(String[] args) throws IOException{
        String content;
        int sum= 0;
        try (FileInputStream fis = new FileInputStream("path/to/file.txt");){
            byte[] buffer = new byte[fis.available()];
            int bytesRead = fis.read(buffer);
            for (int i= 0; i < bytesRead; i++){
                sum += Byte.toUnsignedInt(buffer[i]);
            }
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        if (sum == 0){
            System.out.println("The file is empty");
        } else {
            System.out.println("The checksum of the file: "+ sum);
            System.out.println("Number of bytes read: "+bytesRead);
        }
    }
}