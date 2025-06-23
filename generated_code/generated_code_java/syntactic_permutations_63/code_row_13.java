import java.util.*;
import java.io.*;
public class CalculateChecksum{
    public static void main(String[] args)throws Exception{
        FileInputStream file = new FileInputStream("data.txt");
        BufferedReader reader = new BufferedReader(file);
        StringBuffer buffer = new StringBuffer();

        int checksum = 0;
        while(reader.ready()){
            char ch = (char) reader.read();
            buffer.append(ch);
            checksum += ch;
        }
        if(checksum == 0)
            System.out.println("Buffer is empty");
        FileOutputStream outFile = new FileInputStream("data_output.txt");
        PrintStream ps = new PrintStream(outFile);

        ps.println("Number of bytes read: " + buffer.length());
        ps.println("Checksum: " + checksum);
        file.close();
        outFile.close();
    }
}