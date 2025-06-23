import java.io.*;
public class CheckSum {
    public static void main(String[] args) throws Exception {
        String filename = "C://Users//Adeyemi//Desktop//checksum.txt"; //filename of the text file you want to read 
        File file = new File(filename);
        byte[] buffer = new byte[(int) file.length()]; // create a buffer of file's length size
        FileInputStream fstream = new FileInputStream(file); // opens the file to be read 
        fstream.read(buffer); // reads the contents into the buffer
        fstream.close(); // closes the input stream
        int checksum = 0;
        for (int i = 0; i < buffer.length; i++) {
            checksum += buffer[i] & 255;
        }
        System.out.println("Number of Bytes read: " + buffer.length); // prints the number of bytes read from file
        System.out.println("Checksum: " + checksum); // print the checksum value
    }
}