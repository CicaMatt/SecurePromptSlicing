import java.io.*;

public class FileReader {
    public static void main(String[] args) throws Exception{
        //Reading from a file named "file1"
        FileInputStream fstream = new FileInputStream("file1");
        BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
        
        String strLine;
        int total_bytes=0;
        while ((strLine = br.readLine()) != null)   {
            System.out.println (strLine);
            total_bytes+=strLine.length();
        }
        fstream.close();
        
        FileWriter fr = new FileWriter("file2");
        //Writing data to a file named "file2"
        fr.write(total_bytes+"\r\n");
        fr.close();
    }
}