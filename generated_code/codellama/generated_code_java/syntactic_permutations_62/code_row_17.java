import java.io.File;
import java.nio.*;
import java.nio.file.*;

public class Checksum {
    public static void main(String[] args) throws Exception{
        //Reads the contents of a file into a buffer
        Path path = Paths.get("path/to/file.txt");
        ByteBuffer buff = ByteBuffer.wrap(Files.readAllBytes(path));
        
        //Calculates the checksum of the buffer
        int checksum = 0;
        while(buff.hasRemaining()){
            checksum += (int) buff.get();
        }
        System.out.println("The checksum is: " + checksum);
    }
}